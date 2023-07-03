#include <antlr4-runtime.h>

#include <string>

#include "autogenerated/CEQLQueryLexer.h"
#include "autogenerated/CEQLQueryParser.h"
#include "autogenerated/CEQLQueryParserBaseVisitor.h"
#include "core_server/internal/ceql/query/query.hpp"
#include "visitors/from_visitor.hpp"
#include "visitors/select_visitor.hpp"

//#include "visitors/where_visitor.hpp"

namespace CORE {
namespace Internal {
namespace Parsing {

class QueryVisitor : public CEQLQueryParserBaseVisitor {
  // Override methods from the base visitor to handle
  // specific grammar rules as needed
};

class PartitionByVisitor;
class WithinSegmentVisitor;
class ConsumeByVisitor;

class Parser {
 public:
  static CEQL::Query parse_query(std::string query) {
    // TODO finish this.
    // Convert the input string to a stream
    antlr4::ANTLRInputStream input(query);

    // Use the ANTLR input stream to create a lexer
    CEQLQueryLexer lexer(&input);

    // Use the lexer to create a token stream
    antlr4::CommonTokenStream tokens(&lexer);

    // Use the token stream to create a parser
    CEQLQueryParser parser(&tokens);

    // Parse the input
    antlr4::tree::ParseTree* tree = parser.parse();

    SelectVisitor select_visitor;
    select_visitor.visit(tree);
    CEQL::Select select = select_visitor.get_parsed_select();

    FromVisitor from_visitor;
    from_visitor.visit(tree);
    CEQL::From from = from_visitor.get_parsed_from();

    //WhereVisitor where_visitor;
    //where_visitor.visit(tree);
    //Where where = where_visitor.get_parsed_where();

    // TODO: Add PartitionByVisitor
    // TODO: Add WithinSegmentVisitor
    // TODO: Add ConsumeByVisitor

    //return {std::move(select), std::move(from), std::move(where), {}, {}, {}};

    //return parsedQuery;
  }
};

}  // namespace Parsing
}  // namespace Internal
}  // namespace CORE
