#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "core_server/internal/ceql/query/query.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryLexer.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParser.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParserBaseVisitor.h"
#include "core_server/internal/parsing/ceql_query/visitors/limit_visitor.hpp"

namespace CORE::Internal::CEQL::UnitTests {

std::string create_limit_query(std::string limit) {
  if (limit != "") {
    limit = "LIMIT " + limit;
  }
  // clang-format off
  return "SELECT ALL * \n"
         "FROM S, S2\n"
         "WHERE S>T \n"
         "--WHERE H+ OR H+\n"
         "FILTER\n"
         "    all_events[id NOT IN { 123, 125 }]\n"
         "    AND\n"
         "    ( t2[temp > 50 or temp < 20] OR H[income > 2 * cost] )\n"
         "WITHIN 4 EVENTS\n"
         + limit;
  // clang-format on
}

Limit parse_limit(std::string query) {
  antlr4::ANTLRInputStream input(query);
  CEQLQueryLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQLQueryParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  Parsing::LimitVisitor limit_visitor;
  limit_visitor.visit(tree);
  return limit_visitor.get_parsed_limit();
}

TEST_CASE("Limit captures limit correctly", "[Limit]") {
  // clang-format off
  REQUIRE(parse_limit(create_limit_query("")).result_limit == -1);
  REQUIRE(parse_limit(create_limit_query("1")).result_limit == 1);
  REQUIRE(parse_limit(create_limit_query("1000")).result_limit == 1000);
  // clang-format on
}

}  // namespace CORE::Internal::CEQL::UnitTests
