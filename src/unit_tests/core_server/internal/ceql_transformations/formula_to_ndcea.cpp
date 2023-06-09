#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <memory>

#include "core_server/internal/ceql/cel_formula/formula/visitors/formula_to_logical_cea.hpp"
#include "core_server/internal/ceql/query/query.hpp"
#include "core_server/internal/coordination/catalog.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryLexer.h"
#include "core_server/internal/parsing/ceql_query/visitors/where_visitor.hpp"

namespace CORE::Internal::CEQL::UnitTests::FormulaToNDCEATests {

std::string create_query(std::string clause) {
  // clang-format off
  return "SELECT ALL * \n"
         "FROM S, S2\n"
         "WHERE " + clause + " WITHIN 4 EVENTS\n";
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

std::unique_ptr<CEQL::Formula> parse_formula(std::string query) {
  return std::move(parse_where(query).formula);
}

TEST_CASE("Basic Event Type", "[ValueToMathExpr]") {
  Catalog catalog;
  auto event_type_id = catalog.add_event_type("H", {});
  auto formula = parse_formula(create_query("H"));
  auto visitor = FormulaToCEA(catalog);
  formula->accept_visitor(visitor);
  CEA::LogicalCEA ndcea = visitor.current_cea;
}
}  // namespace CORE::Internal::CEQL::UnitTests::FormulaToNDCEATests
