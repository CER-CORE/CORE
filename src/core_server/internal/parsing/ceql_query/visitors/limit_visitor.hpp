#pragma once

#include <memory>

#include "core_server/internal/ceql/query/limit.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParserBaseVisitor.h"

namespace CORE::Internal::Parsing {
class LimitVisitor : public CEQLQueryParserBaseVisitor {
 private:
  // Default to no limit
  int64_t limit = -1;

 public:
  CEQL::Limit get_parsed_limit() { return CEQL::Limit(limit); }

  virtual std::any visitCore_query(CEQLQueryParser::Core_queryContext* ctx) override {
    if (ctx->limit()) visit(ctx->limit());
    return {};
  }

  virtual std::any visitL_integer(CEQLQueryParser::L_integerContext* ctx) override {
    // getText() returns arbritary positive numbers, therefore must check size
    uint64_t text_limit = std::stoull(ctx->integer()->getText());
    if (text_limit > std::numeric_limits<int64_t>::max()) {
      throw std::runtime_error(
        "Query limit is too large, if you do not wish to set a query limit, remove "
        "Limit from the query");
    }
    limit = static_cast<int64_t>(text_limit);
    return {};
  }
};
}  // namespace CORE::Internal::Parsing
