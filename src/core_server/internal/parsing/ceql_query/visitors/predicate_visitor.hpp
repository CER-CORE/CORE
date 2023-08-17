#pragma once
#include <memory>

#include "core_server/internal/ceql/cel_formula/predicate/predicate_headers.hpp"
#include "core_server/internal/ceql/query/where.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQLQueryParserBaseVisitor.h"
#include "value_visitor.hpp"

namespace CORE::Internal::Parsing {
class PredicateVisitor : public CEQLQueryParserBaseVisitor {
 private:
  // this formula is the corresponding parsed filter after parsing the
  // visitation to the ctx is finished.
  std::unique_ptr<CEQL::Predicate> predicate;

  ValueVisitor value_visitor;

 public:
  std::unique_ptr<CEQL::Predicate> get_parsed_predicate() {
    return std::move(predicate);
  }

  virtual std::any
  visitNot_predicate(CEQLQueryParser::Not_predicateContext* ctx) override {
    visit(ctx->predicate());
    predicate = predicate->negate();
    return {};
  }

  virtual std::any visitInequality_predicate(
    CEQLQueryParser::Inequality_predicateContext* ctx) override {
    value_visitor.visit(ctx->math_expr()[0]);
    std::unique_ptr<CEQL::Value> left = value_visitor.get_parsed_value();
    value_visitor.visit(ctx->math_expr()[1]);
    std::unique_ptr<CEQL::Value> right = value_visitor.get_parsed_value();

    CEQL::InequalityPredicate::LogicalOperation operation;
    if (ctx->LE()) {
      operation = CEQL::InequalityPredicate::LogicalOperation::LESS;
    } else if (ctx->LEQ()) {
      operation = CEQL::InequalityPredicate::LogicalOperation::LESS_EQUALS;
    } else if (ctx->GE()) {
      operation = CEQL::InequalityPredicate::LogicalOperation::GREATER;
    } else if (ctx->GEQ()) {
      operation = CEQL::InequalityPredicate::LogicalOperation::GREATER_EQUALS;
    } else if (ctx->EQ()) {
      operation = CEQL::InequalityPredicate::LogicalOperation::EQUALS;
    } else {
      operation = CEQL::InequalityPredicate::LogicalOperation::NOT_EQUALS;
    }

    predicate = std::make_unique<CEQL::InequalityPredicate>(std::move(left),
                                                            operation,
                                                            std::move(right));
    return {};
  }

  virtual std::any visitEquality_string_predicate(
    CEQLQueryParser::Equality_string_predicateContext* ctx) override {
    value_visitor.visit(ctx->string_literal());
    auto left = value_visitor.get_parsed_value();
    value_visitor.visit(ctx->string_literal_or_regexp());
    auto right = value_visitor.get_parsed_value();

    CEQL::InequalityPredicate::LogicalOperation operation;
    if (ctx->EQ()) {
      operation = CEQL::InequalityPredicate::LogicalOperation::EQUALS;
    } else {
      operation = CEQL::InequalityPredicate::LogicalOperation::NOT_EQUALS;
    }

    predicate = std::make_unique<CEQL::InequalityPredicate>(std::move(left),
                                                            operation,
                                                            std::move(right));
    return {};
  }

  virtual std::any
  visitAnd_predicate(CEQLQueryParser::And_predicateContext* ctx) override {
    std::vector<std::unique_ptr<CEQL::Predicate>> predicates;
    visit(ctx->predicate(0));
    predicates.push_back(std::move(predicate));
    visit(ctx->predicate(1));
    predicates.push_back(std::move(predicate));
    predicate = std::make_unique<CEQL::AndPredicate>(std::move(predicates));
    return {};
  }

  virtual std::any
  visitOr_predicate(CEQLQueryParser::Or_predicateContext* ctx) override {
    std::vector<std::unique_ptr<CEQL::Predicate>> predicates;
    visit(ctx->predicate()[0]);
    predicates.push_back(std::move(predicate));
    visit(ctx->predicate()[1]);
    predicates.push_back(std::move(predicate));
    predicate = std::make_unique<CEQL::OrPredicate>(std::move(predicates));
    return {};
  }

  virtual std::any visitRegex_predicate(
    CEQLQueryParser::Regex_predicateContext* ctx) override {
    value_visitor.visit(ctx->attribute_name());
    auto left = value_visitor.get_parsed_value();
    value_visitor.visit(ctx->regexp());
    auto right = value_visitor.get_parsed_value();
    predicate = std::make_unique<CEQL::LikePredicate>(std::move(left),
                                                      std::move(right));
    return {};
  }

  virtual std::any
  visitIn_predicate(CEQLQueryParser::In_predicateContext* ctx) override {
    value_visitor.visit(ctx->attribute_name());
    auto left = value_visitor.get_parsed_value();

    value_visitor.visit(ctx->value_seq());
    CEQL::Sequence* right_ptr = static_cast<CEQL::Sequence*>(
      value_visitor.get_parsed_value().release());
    assert(right_ptr != nullptr);
    CEQL::Sequence right = std::move(*right_ptr);
    predicate = std::make_unique<CEQL::InPredicate>(std::move(left),
                                                    std::move(right));
    if (ctx->K_NOT()) {
      predicate = std::make_unique<CEQL::NotPredicate>(std::move(predicate));
    }
    return {};
  }

  virtual std::any visitIn_range_predicate(
    CEQLQueryParser::In_range_predicateContext* ctx) override {
    value_visitor.visit(ctx->math_expr()[0]);
    auto left = value_visitor.get_parsed_value();
    value_visitor.visit(ctx->math_expr()[1]);
    auto lower_bound = value_visitor.get_parsed_value();
    value_visitor.visit(ctx->math_expr()[2]);
    auto upper_bound = value_visitor.get_parsed_value();
    predicate = std::make_unique<CEQL::InRangePredicate>(
      std::move(left), std::move(lower_bound), std::move(upper_bound));
    return {};
  }
};
}  // namespace CORE::Internal::Parsing
