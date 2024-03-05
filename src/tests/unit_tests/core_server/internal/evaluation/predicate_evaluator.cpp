#include "core_server/internal/evaluation/predicate_evaluator.hpp"

#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <cstdint>
#include <cstring>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "core_server/internal/ceql/cel_formula/formula/projection_formula.hpp"
#include "core_server/internal/ceql/query/consume_by.hpp"
#include "core_server/internal/ceql/query/from.hpp"
#include "core_server/internal/ceql/query/limit.hpp"
#include "core_server/internal/ceql/query/partition_by.hpp"
#include "core_server/internal/ceql/query/query.hpp"
#include "core_server/internal/ceql/query/select.hpp"
#include "core_server/internal/ceql/query/within.hpp"
#include "core_server/internal/ceql/query_transformer/annotate_predicates_with_new_physical_predicates.hpp"
#include "core_server/internal/coordination/catalog.hpp"
#include "core_server/internal/coordination/query_catalog.hpp"
#include "core_server/internal/evaluation/physical_predicate/physical_predicate.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryLexer.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParser.h"
#include "core_server/internal/parsing/ceql_query/visitors/where_visitor.hpp"
#include "core_server/internal/stream/ring_tuple_queue/queue.hpp"
#include "core_server/internal/stream/ring_tuple_queue/tuple.hpp"
#include "shared/datatypes/catalog/attribute_info.hpp"
#include "shared/datatypes/catalog/datatypes.hpp"
#include "shared/datatypes/catalog/stream_info.hpp"

namespace CORE::Internal::CEA::UnitTests {

std::vector<Types::AttributeInfo> attributes_of_event_type_1() {
  std::vector<Types::AttributeInfo> attributes_info;
  attributes_info.emplace_back("String", Types::ValueTypes::STRING_VIEW);
  attributes_info.emplace_back("Integer1", Types::ValueTypes::INT64);
  attributes_info.emplace_back("Integer2", Types::ValueTypes::INT64);
  attributes_info.emplace_back("Double1", Types::ValueTypes::DOUBLE);
  attributes_info.emplace_back("Double2", Types::ValueTypes::DOUBLE);
  return attributes_info;
}

RingTupleQueue::Tuple add_event_type_1(RingTupleQueue::Queue& ring_tuple_queue,
                                       std::string val1,
                                       int64_t val2,
                                       int64_t val3,
                                       double val4,
                                       double val5) {
  uint64_t* data = ring_tuple_queue.start_tuple(0);
  char* chars = ring_tuple_queue.writer<std::string>(val1.size());
  memcpy(chars, &val1[0], val1.size());
  int64_t* integer_ptr = ring_tuple_queue.writer<int64_t>();
  *integer_ptr = val2;
  integer_ptr = ring_tuple_queue.writer<int64_t>();
  *integer_ptr = val3;
  double* double_ptr = ring_tuple_queue.writer<double>();
  *double_ptr = val4;
  double_ptr = ring_tuple_queue.writer<double>();
  *double_ptr = val5;
  return ring_tuple_queue.get_tuple(data);
}

std::vector<Types::AttributeInfo> attributes_of_event_type_2() {
  std::vector<Types::AttributeInfo> attributes_info;
  attributes_info.emplace_back("Integer1", Types::ValueTypes::INT64);
  attributes_info.emplace_back("Integer2", Types::ValueTypes::INT64);
  return attributes_info;
}

RingTupleQueue::Tuple
add_event_type_2(RingTupleQueue::Queue& ring_tuple_queue, int64_t val1, int64_t val2) {
  uint64_t* data = ring_tuple_queue.start_tuple(1);
  int64_t* integer_ptr = ring_tuple_queue.writer<int64_t>();
  *integer_ptr = val1;
  integer_ptr = ring_tuple_queue.writer<int64_t>();
  *integer_ptr = val2;
  return ring_tuple_queue.get_tuple(data);
}

std::string create_query(std::string filter_clause) {
  // clang-format off
  return "SELECT ALL * \n"
         "FROM S, S2\n"
         "WHERE S>T \n"
         "--WHERE H+ OR H+\n"
         "FILTER\n"
         + filter_clause + "\n"
         "WITHIN 4 EVENTS\n";
  // clang-format on
}

CEQL::Query parse_query(std::string query) {  // Only parses where correctly
  antlr4::ANTLRInputStream input(query);
  CEQLQueryLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQLQueryParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  Parsing::WhereVisitor where_visitor;
  where_visitor.visit(tree);
  std::unique_ptr<CEQL::ProjectionFormula> formula = std::make_unique<
    CEQL::ProjectionFormula>(std::set<std::string>{""},
                             std::set<std::pair<std::string, std::string>>{});

  // TODO: Partitionby, within and consume_by
  CEQL::Query parsed_query(CEQL::Select(CEQL::Select::Strategy::ALL,
                                        true,
                                        std::move(formula)),
                           CEQL::From({}),
                           std::move(where_visitor.get_parsed_where()),
                           CEQL::PartitionBy(),
                           CEQL::Within(),
                           CEQL::ConsumeBy(),
                           CEQL::Limit());
  return parsed_query;
}

std::vector<std::unique_ptr<PhysicalPredicate>>
get_predicates(CEQL::Query& query, Catalog& catalog) {
  QueryCatalog query_catalog(catalog);
  CEQL::AnnotatePredicatesWithNewPhysicalPredicates transformer(query_catalog);
  query = transformer(std::move(query));
  return std::move(transformer.physical_predicates);
}

TEST_CASE(
  "Predicate Evaluator creates the correct mpz_class for CompareMathExprs "
  "(bitset)",
  "[PredicateEvaluator]") {
  Catalog catalog;
  Types::StreamInfo stream_info = catalog.add_stream_type(
    {"event1",
     {{"event1", attributes_of_event_type_1()}, {"event2", attributes_of_event_type_2()}}});
  REQUIRE(stream_info.events_info[0].id == 0);
  REQUIRE(stream_info.events_info[1].id == 1);
  RingTupleQueue::Queue ring_tuple_queue(100, &catalog.tuple_schemas);

  SECTION("StronglyTyped compare with constant") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 >= 20 AND Double1 >= 1.0] AND "
                   "event2[Integer1 <= 30 OR Integer2 > 3]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0001);
  }

  SECTION("StronglyTyped compare with attribute mixed types math_exprs") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 >= Double1 AND Integer2 <= 1.0] AND "
                   "event2[Integer1 >= (Integer1 + 30) / Integer2 AND 6 > Integer2]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b1010);
  }

  SECTION("WeaklyTyped simple comparison predicates") {
    CEQL::Query query = parse_query(
      create_query("X[Integer1 >= 20 AND Double1 >= 1.0] AND "
                   "event2[Integer1 <= 30 OR Integer2 > 3]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_2(ring_tuple_queue, 20, 0);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b1010);
  }

  SECTION("WeaklyTyped complicated comparison predicates") {
    CEQL::Query query = parse_query(
      create_query("X[Integer1 >= 20 AND Integer2 >= Integer1 * 2] AND "
                   "Y[Integer2 >= 30 OR Double1 > 3]"));
    auto predicates = get_predicates(query, catalog);
    INFO("Predicates with size: " + std::to_string(predicates.size()));
    INFO(predicates[0]->complete_info_string());
    INFO(predicates[1]->complete_info_string());
    INFO(predicates[2]->complete_info_string());
    INFO(predicates[3]->complete_info_string());
    auto evaluator = Evaluation::PredicateEvaluator(std::move(predicates));
    RingTupleQueue::Tuple tuple = add_event_type_2(ring_tuple_queue, 20, 40);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b1110);
  }

  SECTION("WeaklyTyped complicated comparison predicates no.2") {
    CEQL::Query query = parse_query(
      create_query("X[NOT((Integer1 - Integer2) * Integer1 / (Double1 + 2) >= "
                   "20 AND NOT (Integer2 >= Integer1 * 2))] AND "
                   "X[Integer1 >= Double1 OR Integer1 == Integer1] AND Y[Integer1 != "
                   "Integer2]"));
    auto predicates = get_predicates(query, catalog);
    INFO("Predicates with size: " + std::to_string(predicates.size()));
    INFO(predicates[0]->complete_info_string());
    INFO(predicates[1]->complete_info_string());
    INFO(predicates[2]->complete_info_string());
    INFO(predicates[3]->complete_info_string());
    INFO(predicates[4]->complete_info_string());
    auto evaluator = Evaluation::PredicateEvaluator(std::move(predicates));
    RingTupleQueue::Tuple tuple = add_event_type_2(ring_tuple_queue, 20, 40);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b11110);
  }

  SECTION("IN predicate works correctly") {
    // TODO
  }

  SECTION("StronglyTyped LIKE predicate matching") {
    CEQL::Query query = parse_query(create_query("event1[String LIKE <<.*>>]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0010);
  }

  SECTION("StronglyTyped LIKE predicate not matching") {
    CEQL::Query query = parse_query(create_query("event1[String LIKE <<.>>]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0010);
  }

  SECTION("WeaklyTyped LIKE predicate matching") {
    CEQL::Query query = parse_query(create_query("X[String LIKE <<.*>>]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0010);
  }

  SECTION("WeaklyTyped LIKE predicate not matching") {
    CEQL::Query query = parse_query(create_query("X[String LIKE <<.>>]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b0010);
  }

  SECTION("StronglyTyped IN RANGE (int, int) predicate complex true") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 IN RANGE (((Integer2*100)/120), "
                   "Integer1 * Integer2)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   292,
                                                   350,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("StronglyTyped IN RANGE (int, int) predicate complex false") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 IN RANGE (((Integer2*100)/120), "
                   "Integer1 * Integer2)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   150,
                                                   200,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("StronglyTyped IN RANGE (int, int) predicate trivially false") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 IN RANGE (Integer1, Integer2)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   19,
                                                   0.0,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("StronglyTyped IN RANGE predicate mixed types match") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 IN RANGE (Integer1, Double1)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   19,
                                                   20.5,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("StronglyTyped IN RANGE predicate mixed types not match") {
    CEQL::Query query = parse_query(
      create_query("event1[Integer1 IN RANGE (Integer1, Double1)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   19,
                                                   19.8,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("WeaklyTyped IN RANGE predicate myxed types matching") {
    CEQL::Query query = parse_query(
      create_query("X[Integer1 IN RANGE (Integer1, Double1)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   0,
                                                   25.5,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 5);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("WeaklyTyped IN RANGE predicate (int, int) matching") {
    CEQL::Query query = parse_query(
      create_query("X[Integer1 IN RANGE (Integer1, Integer2)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   25,
                                                   25.5,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b101);
    tuple = add_event_type_2(ring_tuple_queue, 20, 21);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b110);
  }

  SECTION("WeaklyTyped IN RANGE predicate (int, int) not matching") {
    CEQL::Query query = parse_query(
      create_query("X[Integer1 IN RANGE (Integer1, Integer2)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   15,
                                                   25.5,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 18);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }

  SECTION("WeaklyTyped IN RANGE predicate mixed types not matching") {
    CEQL::Query query = parse_query(
      create_query("X[Integer1 IN RANGE (Integer1, Double1)]"));
    auto evaluator = Evaluation::PredicateEvaluator(get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_1(ring_tuple_queue,
                                                   "somestring",
                                                   20,
                                                   25,
                                                   18.5,
                                                   1.2);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b001);
    tuple = add_event_type_2(ring_tuple_queue, 20, 21);
    evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b010);
  }
}
}  // namespace CORE::Internal::CEA::UnitTests
