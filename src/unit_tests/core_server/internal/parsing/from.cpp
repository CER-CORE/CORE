#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "core_server/internal/ceql/query/query.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYBaseVisitor.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYLexer.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYParser.h"
#include "core_server/internal/parsing/ceql_query/visitors/from_visitor.hpp"

using namespace InternalCORECEQLParsing;

namespace COREQueryParsingTests {

std::string create_from_query(std::string stream_names) {
  // clang-format off
  return "SELECT ALL *\n"
         "FROM " + stream_names + "\n"
         "WHERE ( S>T ; H + ; T AS t2 ) AS all_events\n"
         "--WHERE H+ OR H+\n"
         "FILTER\n"
         "    all_events[id NOT IN { 123, 125 }]\n"
         "    AND\n"
         "    ( t2[temp > 50 or temp < 20] OR H[income > 2 * cost] )\n"
         "WITHIN 4 EVENTS\n";
  // clang-format on
}

std::string query_without_from() {
  // clang-format off
  return "SELECT ALL *\n"
         "WHERE ( S>T ; H + ; T AS t2 ) AS all_events\n"
         "--WHERE H+ OR H+\n"
         "FILTER\n"
         "    all_events[id NOT IN { 123, 125 }]\n"
         "    AND\n"
         "    ( t2[temp > 50 or temp < 20] OR H[income > 2 * cost] )\n"
         "WITHIN 4 EVENTS\n";
  // clang-format on
}

From parse_from(std::string query) {
  antlr4::ANTLRInputStream input(query);
  CEQL_QUERYLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQL_QUERYParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  FromVisitor from_visitor;
  from_visitor.visit(tree);
  return from_visitor.get_parsed_from();
}

TEST_CASE("From captures list_of_streams correctly",
          "[From, list_of_variables]") {
  std::set<std::string> stream_names;
  bool condition;

  stream_names = parse_from(create_from_query("A1")).streams;
  condition = stream_names.contains("A1") && stream_names.size() == 1;
  REQUIRE(condition);

  stream_names = parse_from(create_from_query("A1, A2")).streams;
  condition = stream_names.contains("A1") && stream_names.contains("A1") &&
              stream_names.size() == 2;
  REQUIRE(condition);

  stream_names = parse_from(create_from_query("A1, A2, A2")).streams;
  condition = stream_names.contains("A1") && stream_names.contains("A1") &&
              stream_names.size() == 2;
  REQUIRE(condition);

  stream_names = parse_from(query_without_from()).streams;
  condition = stream_names.size() == 0;
  REQUIRE(condition);
}
}  // namespace COREQueryParsingTests
