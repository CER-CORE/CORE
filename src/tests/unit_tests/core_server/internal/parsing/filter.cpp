#include "core_server/internal/ceql/cel_formula/filters/filter.hpp"

#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <memory>
#include <string>
#include <utility>

#include "core_server/internal/ceql/cel_formula/filters/and_filter.hpp"
#include "core_server/internal/ceql/cel_formula/filters/atomic_filter.hpp"
#include "core_server/internal/ceql/cel_formula/filters/or_filter.hpp"
#include "core_server/internal/ceql/cel_formula/formula/filter_formula.hpp"
#include "core_server/internal/ceql/cel_formula/formula/formula.hpp"
#include "core_server/internal/ceql/cel_formula/predicate/inequality_predicate.hpp"
#include "core_server/internal/ceql/query/where.hpp"
#include "core_server/internal/ceql/value/attribute.hpp"
#include "core_server/internal/ceql/value/integer_literal.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryLexer.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParser.h"
#include "core_server/internal/parsing/ceql_query/visitors/where_visitor.hpp"

namespace CORE::Internal::CEQL::UnitTests::FilterTests {

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

Where parse_where(std::string query) {
  antlr4::ANTLRInputStream input(query);
  CEQLQueryLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQLQueryParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  Parsing::WhereVisitor where_visitor;
  where_visitor.visit(tree);
  return where_visitor.get_parsed_where();
}

template <typename T>
std::unique_ptr<T> cast_to(std::unique_ptr<Formula> unknown) {
  std::unique_ptr<T> casted_optional(dynamic_cast<T*>(unknown.release()));
  return casted_optional;
}

template <typename T>
std::unique_ptr<T> cast_to(std::unique_ptr<Filter> unknown) {
  std::unique_ptr<T> casted_optional(dynamic_cast<T*>(unknown.release()));
  return casted_optional;
}

/***********************************/
/* Single functionality unit tests */
/***********************************/

/*************************/
/* Inequality Predicates */
/*************************/

std::unique_ptr<Filter> parse_filter(std::string query) {
  auto where = std::move(parse_where(query));
  auto formula = std::move(where.formula);
  REQUIRE(formula != nullptr);
  auto filter_formula = cast_to<FilterFormula>(std::move(formula));
  REQUIRE(filter_formula != nullptr);
  auto filter = std::move(filter_formula->filter);
  return std::move(filter);
}

using std::make_unique;

TEST_CASE("atomic filter works", "[Predicate, Inequality]") {
  auto query = create_query("t2[temp == 50]");
  std::unique_ptr<Filter> filter = parse_filter(query);
  auto expected_filter = make_unique<AtomicFilter>(
    "t2",
    make_unique<InequalityPredicate>(make_unique<Attribute>("temp"),
                                     InequalityPredicate::LogicalOperation::EQUALS,
                                     make_unique<IntegerLiteral>(50)));
  INFO("Expected: " + expected_filter->to_string());
  INFO("Got: " + filter->to_string());
  REQUIRE(filter->equals(expected_filter.get()));
}

TEST_CASE("atomic filter works with name and stream", "[Predicate, Inequality]") {
  auto query = create_query("S1>t2[temp == 50]");
  std::unique_ptr<Filter> filter = parse_filter(query);
  auto expected_filter = make_unique<AtomicFilter>(
    "S1",
    "t2",
    make_unique<InequalityPredicate>(make_unique<Attribute>("temp"),
                                     InequalityPredicate::LogicalOperation::EQUALS,
                                     make_unique<IntegerLiteral>(50)));
  INFO("Expected: " + expected_filter->to_string());
  INFO("Got: " + filter->to_string());
  REQUIRE(filter->equals(expected_filter.get()));
}

TEST_CASE("and filter works", "[Predicate, Inequality]") {
  auto query = create_query("t2[temp == 50] and t3[temp == 50]");
  std::unique_ptr<Filter> filter = parse_filter(query);
  auto expected_filter = make_unique<AndFilter>(
    make_unique<AtomicFilter>(
      "t2",
      make_unique<InequalityPredicate>(make_unique<Attribute>("temp"),
                                       InequalityPredicate::LogicalOperation::EQUALS,
                                       make_unique<IntegerLiteral>(50))),
    make_unique<AtomicFilter>(
      "t3",
      make_unique<InequalityPredicate>(make_unique<Attribute>("temp"),
                                       InequalityPredicate::LogicalOperation::EQUALS,
                                       make_unique<IntegerLiteral>(50))));
  INFO("Expected: " + expected_filter->to_string());
  INFO("Got: " + filter->to_string());
  REQUIRE(filter->equals(expected_filter.get()));
}

TEST_CASE("or filter works", "[Predicate, Inequality]") {
  auto query = create_query("t2[temp == 50] or t3[temp == 50]");
  std::unique_ptr<Filter> filter = parse_filter(query);
  auto expected_filter = make_unique<OrFilter>(
    make_unique<AtomicFilter>(
      "t2",
      make_unique<InequalityPredicate>(make_unique<Attribute>("temp"),
                                       InequalityPredicate::LogicalOperation::EQUALS,
                                       make_unique<IntegerLiteral>(50))),
    make_unique<AtomicFilter>(
      "t3",
      make_unique<InequalityPredicate>(make_unique<Attribute>("temp"),
                                       InequalityPredicate::LogicalOperation::EQUALS,
                                       make_unique<IntegerLiteral>(50))));
  INFO("Expected: " + expected_filter->to_string());
  INFO("Got: " + filter->to_string());
  REQUIRE(filter->equals(expected_filter.get()));
}

}  // namespace CORE::Internal::CEQL::UnitTests::FilterTests
