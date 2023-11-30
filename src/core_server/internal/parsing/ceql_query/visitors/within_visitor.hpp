#pragma once

#include <memory>

#include "core_server/internal/ceql/query/within.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParserBaseVisitor.h"

namespace CORE::Internal::Parsing {
class WithinVisitor : public CEQLQueryParserBaseVisitor {
 private:
  CEQL::Within within = {};

 public:
  CEQL::Within get_parsed_within() { return std::move(within); }

  virtual std::any
  visitCore_query(CEQLQueryParser::Core_queryContext* ctx) override {
    if (ctx->time_window())
      visit(ctx->time_window());  // Only interested in time_window.
    return {};
  }

  virtual std::any
  visitEvent_span(CEQLQueryParser::Event_spanContext* ctx) override {
    uint64_t amount_of_events = std::stoull(ctx->integer()->getText());
    within.time_window = {amount_of_events,
                          CEQL::Within::TimeWindowMode::EVENTS};
    return {};
  }

  virtual std::any
  visitHour_span(CEQLQueryParser::Hour_spanContext* ctx) override {
    double hours = std::stod(ctx->number()->getText());
    uint64_t ns = static_cast<uint64_t>(hours) * 60 * 60 * 1000 * 1000
                  * 1000;
    within.time_window = {ns, CEQL::Within::TimeWindowMode::NANOSECONDS};
    return {};
  }

  virtual std::any
  visitMinute_span(CEQLQueryParser::Minute_spanContext* ctx) override {
    double minutes = std::stod(ctx->number()->getText());
    uint64_t ns = static_cast<uint64_t>(minutes) * 60 * 1000 * 1000 * 1000;
    within.time_window = {ns, CEQL::Within::TimeWindowMode::NANOSECONDS};
    return {};
  }

  virtual std::any
  visitSecond_span(CEQLQueryParser::Second_spanContext* ctx) override {
    double seconds = std::stod(ctx->number()->getText());
    uint64_t ns = static_cast<uint64_t>(seconds) * 1000 * 1000 * 1000;
    within.time_window = {ns, CEQL::Within::TimeWindowMode::NANOSECONDS};
    return {};
  }

  virtual std::any
  visitCustom_span(CEQLQueryParser::Custom_spanContext* ctx) override {
    within.time_window = {std::stoull(ctx->integer()->getText()),
                          ctx->any_name()->getText(),
                          CEQL::Within::TimeWindowMode::ATTRIBUTE};
    return {};
  }
};
}  // namespace CORE::Internal::Parsing
