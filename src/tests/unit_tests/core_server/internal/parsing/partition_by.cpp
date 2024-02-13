#include "core_server/internal/ceql/query/partition_by.hpp"

#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <string>

#include "core_server/internal/ceql/value/attribute.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryLexer.h"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParser.h"
#include "core_server/internal/parsing/ceql_query/visitors/partition_by_visitor.hpp"

namespace CORE::Internal::CEQL::UnitTests {

std::string create_partition_by_query(std::string partition_by) {
  if (partition_by != "") {
    partition_by = "PARTITION BY " + partition_by;
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
         + partition_by
         + "\nWITHIN 4 EVENTS\n";
  // clang-format on
}

PartitionBy parse_partition_by(std::string query) {
  antlr4::ANTLRInputStream input(query);
  CEQLQueryLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  CEQLQueryParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  Parsing::PartitionByVisitor partition_by_visitor;
  partition_by_visitor.visit(tree);
  return partition_by_visitor.get_parsed_partition_by();
}

TEST_CASE("Partition by captures single attribute correctly", "[Partition By]") {
  // clang-format off
  REQUIRE(parse_partition_by(create_partition_by_query("")).partition_attributes.size() == 0);
  REQUIRE(parse_partition_by(create_partition_by_query("[name]")).partition_attributes.size() == 1);
  REQUIRE(parse_partition_by(create_partition_by_query("[name]")).partition_attributes[0].size() == 1);
  REQUIRE(parse_partition_by(create_partition_by_query("[name]")).partition_attributes[0][0] == CEQL::Attribute("name"));
  // clang-format on
}

TEST_CASE("Partition by captures single attribute with alternative correctly",
          "[Partition By]") {
  // clang-format off
  REQUIRE(parse_partition_by(create_partition_by_query("[name, name2]")).partition_attributes.size() == 1);
  REQUIRE(parse_partition_by(create_partition_by_query("[name, name2]")).partition_attributes[0].size() == 2);
  REQUIRE(parse_partition_by(create_partition_by_query("[name, name2]")).partition_attributes[0][0] == CEQL::Attribute("name"));
  REQUIRE(parse_partition_by(create_partition_by_query("[name, name2]")).partition_attributes[0][1] == CEQL::Attribute("name2"));
  // clang-format on
}

TEST_CASE("Partition by captures two attributes correctly", "[Partition By]") {
  // clang-format off
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2]")).partition_attributes.size() == 2);
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2]")).partition_attributes[0].size() == 1);
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2]")).partition_attributes[1].size() == 1);
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2]")).partition_attributes[0][0] == CEQL::Attribute("name"));
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2]")).partition_attributes[1][0] == CEQL::Attribute("name2"));
  // clang-format on
}

TEST_CASE("Partition by captures two attributes with alternative correctly",
          "[Partition By]") {
  // clang-format off
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2, name3]")).partition_attributes.size() == 2);
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2, name3]")).partition_attributes[0].size() == 1);
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2, name3]")).partition_attributes[1].size() == 2);
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2, name3]")).partition_attributes[0][0] == CEQL::Attribute("name"));
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2, name3]")).partition_attributes[1][0] == CEQL::Attribute("name2"));
  REQUIRE(parse_partition_by(create_partition_by_query("[name], [name2, name3]")).partition_attributes[1][1] == CEQL::Attribute("name3"));
  // clang-format on
}
}  // namespace CORE::Internal::CEQL::UnitTests
