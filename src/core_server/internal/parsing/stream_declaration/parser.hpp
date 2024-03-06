#pragma once

#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <antlr4-runtime.h>
#include <tree/ParseTree.h>

#include <string>

#include "autogenerated/StreamDeclarationLexer.h"
#include "autogenerated/StreamDeclarationParser.h"
#include "shared/datatypes/parsing/stream_info_parsed.hpp"
#include "visitors/stream_visitor.hpp"

namespace CORE::Internal::Parsing::Declaration {

class Parser {
 public:
  static Types::StreamInfoParsed parse_stream(std::string stream) {
    // Convert the input string to a stream
    antlr4::ANTLRInputStream input(stream);

    // Use the ANTLR input stream to create a lexer
    StreamDeclarationLexer lexer(&input);

    // Use the lexer to create a token stream
    antlr4::CommonTokenStream tokens(&lexer);

    // Use the token stream to create a parser
    StreamDeclarationParser parser(&tokens);

    // Parse the input
    antlr4::tree::ParseTree* tree = parser.parse();

    StreamVisitor stream_visitor;
    stream_visitor.visit(tree);
    Types::StreamInfoParsed stream_created = stream_visitor.get_parsed_stream();

    return stream_created;
  }
};
}  // namespace CORE::Internal::Parsing::Declaration
