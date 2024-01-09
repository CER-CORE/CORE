#pragma once

#include <memory>

#include "core_server/internal/ceql/cel_formula/formula/formula_headers.hpp"
#include "core_server/internal/ceql/query/where.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParserBaseVisitor.h"
#include "filter_visitor.hpp"

namespace CORE::Internal::Parsing {
class WhereVisitor : public CEQLQueryParserBaseVisitor {
 private:
  // this formula is the corresponding parsed formula after parsing the
  // visitation to the ctx is finished.
  std::unique_ptr<CEQL::Formula> formula;

  FilterVisitor filter_visitor;

 public:
  CEQL::Where get_parsed_where() { return CEQL::Where(std::move(formula)); }

  virtual std::any visitCore_query(CEQLQueryParser::Core_queryContext* ctx) override {
    // Visiting Where clause will identify all streams.
    auto cel_formula_ctx = ctx->cel_formula();
    visit(cel_formula_ctx);
    return {};  // Only interested in stream names
  }

  virtual std::any visitEvent_type_cel_formula(
    CEQLQueryParser::Event_type_cel_formulaContext* ctx) override {
    formula = std::make_unique<CEQL::EventTypeFormula>(ctx->getText());
    return {};
  }

  virtual std::any
  visitAs_cel_formula(CEQLQueryParser::As_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula());
    formula = std::make_unique<CEQL::AsFormula>(std::move(formula),
                                                ctx->event_name()->getText());
    return {};
  }

  virtual std::any visitNon_contiguous_iteration_cel_formula(
    CEQLQueryParser::Non_contiguous_iteration_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula());
    formula = std::make_unique<CEQL::NonContiguousIterationFormula>(std::move(formula));
    return {};
  }

  virtual std::any visitNon_contiguous_sequencing_cel_formula(
    CEQLQueryParser::Non_contiguous_sequencing_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula()[0]);
    auto first_formula = std::move(formula);
    visit(ctx->cel_formula()[1]);
    formula = std::make_unique<CEQL::NonContiguousSequencingFormula>(std::move(
                                                                       first_formula),
                                                                     std::move(formula));
    return {};
  }

  virtual std::any visitContiguous_sequencing_cel_formula(
    CEQLQueryParser::Contiguous_sequencing_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula()[0]);
    auto first_formula = std::move(formula);
    visit(ctx->cel_formula()[1]);
    formula = std::make_unique<CEQL::ContiguousSequencingFormula>(std::move(first_formula),
                                                                  std::move(formula));
    return {};
  }

  virtual std::any
  visitOr_cel_formula(CEQLQueryParser::Or_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula()[0]);
    auto first_formula = std::move(formula);
    visit(ctx->cel_formula()[1]);
    formula = std::make_unique<CEQL::OrFormula>(std::move(first_formula),
                                                std::move(formula));
    return {};
  }

  virtual std::any
  visitFilter_cel_formula(CEQLQueryParser::Filter_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula());
    filter_visitor.visit(ctx->filter());
    formula = std::make_unique<CEQL::FilterFormula>(std::move(formula),
                                                    filter_visitor.get_parsed_filter());
    return {};
  }

  virtual std::any visitContiguous_iteration_cel_formula(
    CEQLQueryParser::Contiguous_iteration_cel_formulaContext* ctx) override {
    visit(ctx->cel_formula());
    formula = std::make_unique<CEQL::ContiguousIterationFormula>(std::move(formula));
    return {};
  }
};
}  // namespace CORE::Internal::Parsing
