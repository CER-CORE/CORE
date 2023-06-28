#include "core_server/internal/evaluation/predicate_evaluator.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <memory>

#include "core_server/internal/cea/physical_predicate/compare_math_exprs.hpp"
#include "core_server/internal/cea/physical_predicate/compare_with_attribute.hpp"
#include "core_server/internal/cea/physical_predicate/compare_with_constant.hpp"
#include "core_server/internal/ceql/query_transformer/annotate_predicates_with_new_physical_predicates.hpp"
#include "core_server/internal/coordination/catalog.hpp"
#include "core_server/internal/evaluation/predicate_evaluator.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryLexer.h"
#include "core_server/internal/parsing/ceql_query/visitors/where_visitor.hpp"

namespace InternalCORECEAEvaluationTests {
using namespace InternalCORECEA;
using namespace InternalCORECEQLParsing;

std::vector<AttributeInfo> attributes_of_event_type_1() {
  std::vector<AttributeInfo> attributes_info;
  attributes_info.emplace_back("String", CORETypes::ValueTypes::STRING_VIEW);
  attributes_info.emplace_back("Integer1", CORETypes::ValueTypes::INT64);
  attributes_info.emplace_back("Integer2", CORETypes::ValueTypes::INT64);
  attributes_info.emplace_back("Double1", CORETypes::ValueTypes::DOUBLE);
  attributes_info.emplace_back("Double2", CORETypes::ValueTypes::DOUBLE);
  return attributes_info;
}

RingTupleQueue::Tuple
add_event_type_1(RingTupleQueue::Queue& ring_tuple_queue,
                 std::string val1,
                 int64_t val2,
                 int64_t val3,
                 double val4,
                 double val5) {
  std::span<uint64_t> data = ring_tuple_queue.start_tuple(0);
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

std::vector<AttributeInfo> attributes_of_event_type_2() {
  std::vector<AttributeInfo> attributes_info;
  attributes_info.emplace_back("Integer1", CORETypes::ValueTypes::INT64);
  attributes_info.emplace_back("Integer2", CORETypes::ValueTypes::INT64);
  return attributes_info;
}

RingTupleQueue::Tuple
add_event_type_2(RingTupleQueue::Queue& ring_tuple_queue,
                 int64_t val1,
                 int64_t val2) {
  std::span<uint64_t> data = ring_tuple_queue.start_tuple(1);
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

Query parse_query(std::string query) {  // Only parses where correctly
  antlr4::ANTLRInputStream input(query);
  CEQLQueryLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQLQueryParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  WhereVisitor where_visitor;
  where_visitor.visit(tree);
  Query parsed_query(Select(Select::Strategy::ALL, {}, true),
                     From({}),
                     std::move(where_visitor.get_parsed_where()),
                     PartitionBy(),
                     Within(),
                     ConsumeBy());
  return parsed_query;
}

std::vector<std::unique_ptr<PhysicalPredicate>>
get_predicates(Query& query, InternalCORE::Catalog& catalog) {
  AnnotatePredicatesWithNewPhysicalPredicates transformer(catalog);
  query = transformer(std::move(query));
  return std::move(transformer.physical_predicates);
}

TEST_CASE(
  "Predicate Evaluator creates the correct mpz_class for CompareMathExprs "
  "(bitset)",
  "[PredicateEvaluator]") {
  InternalCORE::Catalog catalog;
  EventTypeId event1_id = catalog.add_event_type("event1",
                                                 attributes_of_event_type_1());
  EventTypeId event2_id = catalog.add_event_type("event2",
                                                 attributes_of_event_type_2());
  REQUIRE(event1_id == 0);
  REQUIRE(event2_id == 1);
  RingTupleQueue::Queue ring_tuple_queue(100, &catalog.tuple_schemas);

  SECTION("StronglyTyped compare with constant") {
    Query query = parse_query(
      create_query("event1[Integer1 >= 20 AND Double1 >= 1.0] AND "
                   "event2[Integer1 <= 30 OR Integer2 > 3]"));
    auto evaluator = InternalCOREEvaluation::PredicateEvaluator(
      get_predicates(query, catalog));
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
    Query query = parse_query(create_query(
      "event1[Integer1 >= Double1 AND Integer2 <= 1.0] AND "
      "event2[Integer1 >= (Integer1 + 30) / Integer2 AND 6 > Integer2]"));
    auto evaluator = InternalCOREEvaluation::PredicateEvaluator(
      get_predicates(query, catalog));
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
    Query query = parse_query(
      create_query("X[Integer1 >= 20 AND Double1 >= 1.0] AND "
                   "event2[Integer1 <= 30 OR Integer2 > 3]"));
    auto evaluator = InternalCOREEvaluation::PredicateEvaluator(
      get_predicates(query, catalog));
    RingTupleQueue::Tuple tuple = add_event_type_2(ring_tuple_queue, 20, 0);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b1010);
  }

  SECTION("WeaklyTyped complicated comparison predicates") {
    Query query = parse_query(
      create_query("X[Integer1 >= 20 AND Integer2 >= Integer1 * 2] AND "
                   "Y[Integer2 >= 30 OR Double1 > 3]"));
    auto predicates = get_predicates(query, catalog);
    INFO("Predicates with size: " + std::to_string(predicates.size()));
    INFO(predicates[0]->complete_info_string());
    INFO(predicates[1]->complete_info_string());
    INFO(predicates[2]->complete_info_string());
    INFO(predicates[3]->complete_info_string());
    auto evaluator = InternalCOREEvaluation::PredicateEvaluator(
      std::move(predicates));
    RingTupleQueue::Tuple tuple = add_event_type_2(ring_tuple_queue, 20, 40);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b1110);
  }

  SECTION("WeaklyTyped complicated comparison predicates no.2") {
    Query query = parse_query(create_query(
      "X[NOT((Integer1 - Integer2) * Integer1 / (Double1 + 2) >= "
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
    auto evaluator = InternalCOREEvaluation::PredicateEvaluator(
      std::move(predicates));
    RingTupleQueue::Tuple tuple = add_event_type_2(ring_tuple_queue, 20, 40);
    auto evaluation = evaluator(tuple);
    REQUIRE(evaluation == 0b11110);
  }

  SECTION("IN predicate works correctly") {
    // TODO
  }

  SECTION("LIKE predicate") {
    // TODO
  }
}
}  // namespace InternalCORECEAEvaluationTests
