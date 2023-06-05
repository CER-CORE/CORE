#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "core_server/internal/ceql/query/query.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYBaseVisitor.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYLexer.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYParser.h"
#include "core_server/internal/parsing/ceql_query/visitors/where_visitor.hpp"

using namespace InternalCORECEQLParsing;

namespace COREQueryParsingTestsWhere {

std::string create_where_query(std::string where_clause) {
  // clang-format off
  return "SELECT ALL * \n"
         "FROM S, S2\n"
         "WHERE " + where_clause + "\n"
         "--WHERE H+ OR H+\n"
         "WITHIN 4 EVENTS\n";
  // clang-format on
}

Where parse_where(std::string query) {
  antlr4::ANTLRInputStream input(query);
  CEQL_QUERYLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQL_QUERYParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  WhereVisitor where_visitor;
  where_visitor.visit(tree);
  return where_visitor.get_parsed_where();
}

std::unique_ptr<Formula> parse_formula(std::string query) {
  return std::move(parse_where(query).formula);
}

using std::make_unique;

TEST_CASE("EventType stream>name syntax", "[Where]") {
  auto query = create_where_query("S>T");
  auto expected_formula = make_unique<EventTypeFormula>("S>T");
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

TEST_CASE("EventType name syntax", "[Where]") {
  auto query = create_where_query("T");
  auto expected_formula = make_unique<EventTypeFormula>("T");
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

TEST_CASE("AS", "[Where]") {
  auto query = create_where_query("T as t2");
  auto expected_formula =
      make_unique<AsFormula>(make_unique<EventTypeFormula>("T"), "t2");
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

TEST_CASE("event+", "[Where]") {
  auto query = create_where_query("H+");
  auto expected_formula =
      make_unique<IterationFormula>(make_unique<EventTypeFormula>("H"));
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

TEST_CASE("event;event", "[Where]") {
  auto query = create_where_query("H;T");
  auto expected_formula =
      make_unique<SequencingFormula>(
          make_unique<EventTypeFormula>("H"),
          make_unique<EventTypeFormula>("T")
          );
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

TEST_CASE("event or event", "[Where]") {
  auto query = create_where_query("H OR T");
  auto expected_formula =
      make_unique<OrFormula>(
          make_unique<EventTypeFormula>("H"),
          make_unique<EventTypeFormula>("T")
          );
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

// Filters checked at filter.cpp

TEST_CASE("Example test", "[Where, Composite]") {
  auto query = create_where_query("( S>T ; H + ; T AS t2) AS all_events");
  auto expected_formula = make_unique<AsFormula>(
      make_unique<SequencingFormula>(
          make_unique<SequencingFormula>(
              make_unique<EventTypeFormula>("S>T"),
              make_unique<IterationFormula>(
                  make_unique<EventTypeFormula>("H"))),
          make_unique<AsFormula>(make_unique<EventTypeFormula>("T"),
                                 "t2")),
      "all_events");
  auto formula = parse_formula(query);
  INFO("Expected: " + expected_formula->to_string());
  INFO("Got: " + formula->to_string());
  REQUIRE(formula->equals(expected_formula.get()));
}

}  // namespace COREQueryParsingTestsWhere
