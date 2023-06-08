#include "core_server/internal/ceql/query/from.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYBaseVisitor.h"

using namespace InternalCORECEQL;

namespace InternalCORECEQLParsing {
class FromVisitor : public CEQL_QUERYBaseVisitor {
 private:
  std::set<std::string> streams;

 public:
  From get_parsed_from() { return From(std::move(streams)); }

  virtual std::any visitCore_query(
      CEQL_QUERYParser::Core_queryContext* ctx) override {
    // Visiting From clause will identify all streams.
    auto from_ctx = ctx->from_clause();
    if (from_ctx) {
      visit(from_ctx);
    }
    return {};  // Only interested in stream names
  }

  virtual std::any visitStream_name(
      CEQL_QUERYParser::Stream_nameContext* ctx) override {
    streams.insert(ctx->getText());
    return {};
  }
};
}  // namespace InternalCORECEQLParsing