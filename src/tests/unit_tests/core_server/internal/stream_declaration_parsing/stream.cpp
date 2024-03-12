#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <string>

#include "core_server/internal/parsing/stream_declaration/autogenerated/StreamDeclarationLexer.h"
#include "core_server/internal/parsing/stream_declaration/autogenerated/StreamDeclarationParser.h"
#include "core_server/internal/parsing/stream_declaration/visitors/stream_visitor.hpp"
#include "shared/datatypes/catalog/datatypes.hpp"
#include "shared/datatypes/parsing/event_info_parsed.hpp"
#include "shared/datatypes/parsing/stream_info_parsed.hpp"

namespace CORE::Internal::CEQL::UnitTests {

Types::StreamInfoParsed parse_stream(std::string stream) {
  antlr4::ANTLRInputStream input(stream);
  StreamDeclarationLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  StreamDeclarationParser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.parse();
  Parsing::Declaration::StreamVisitor stream_visitor;
  stream_visitor.visit(tree);
  return stream_visitor.get_parsed_stream();
}

TEST_CASE("Correct stream visitor parsing") {
  std::string declaration =
    "DECLARE STREAM MySensor {\n"
    "EVENT Temp { ID:int, Value1:string, Value2:boolean },\n"
    "EVENT Hum { ID:int, Value3:double },\n"
    "EVENT Hum2 { ID:int }\n"
    "}";
  Types::StreamInfoParsed stream = parse_stream(declaration);

  REQUIRE(stream.name == "MySensor");

  Types::EventInfoParsed first_event = stream.events_info[0];

  REQUIRE(first_event.name == "Temp");
  REQUIRE(first_event.attributes_info[0].name == "ID");
  REQUIRE(first_event.attributes_info[0].value_type == Types::ValueTypes::INT64);
  REQUIRE(first_event.attributes_info[1].name == "Value1");
  REQUIRE(first_event.attributes_info[1].value_type == Types::ValueTypes::STRING_VIEW);
  REQUIRE(first_event.attributes_info[2].name == "Value2");
  REQUIRE(first_event.attributes_info[2].value_type == Types::ValueTypes::BOOL);

  Types::EventInfoParsed second_event = stream.events_info[1];

  REQUIRE(second_event.name == "Hum");
  REQUIRE(second_event.attributes_info[0].name == "ID");
  REQUIRE(second_event.attributes_info[0].value_type == Types::ValueTypes::INT64);
  REQUIRE(second_event.attributes_info[1].name == "Value3");
  REQUIRE(second_event.attributes_info[1].value_type == Types::ValueTypes::DOUBLE);

  Types::EventInfoParsed third_event = stream.events_info[2];

  REQUIRE(third_event.name == "Hum2");
  REQUIRE(third_event.attributes_info[0].name == "ID");
  REQUIRE(third_event.attributes_info[0].value_type == Types::ValueTypes::INT64);
}

}  // namespace CORE::Internal::CEQL::UnitTests