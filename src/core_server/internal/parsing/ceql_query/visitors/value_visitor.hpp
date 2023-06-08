#pragma once

#include "core_server/internal/ceql/query/where.hpp"
#include "core_server/internal/ceql/value/all_value_headers.hpp"
#include "core_server/internal/parsing/ceql_query/autogenerated/CEQL_QUERYBaseVisitor.h"

using namespace InternalCORECEQL;

namespace InternalCORECEQLParsing {
class ValueVisitor : public CEQL_QUERYBaseVisitor {
 private:
  // this formula is the corresponding parsed filter after parsing the
  // visitation to the ctx is finished.
  std::unique_ptr<Value> value;

 public:
  std::unique_ptr<Value> get_parsed_value() { return std::move(value); }

  virtual std::any visitInteger(
      CEQL_QUERYParser::IntegerContext* ctx) override {
    std::string integer_string = ctx->getText();
    value = std::make_unique<IntegerLiteral>(std::stoll(integer_string));
    return {};
  }

  virtual std::any visitDouble(
      CEQL_QUERYParser::DoubleContext* ctx) override {
    std::string double_string = ctx->getText();
    value = std::make_unique<DoubleLiteral>(std::stod(double_string));
    return {};
  }

  virtual std::any visitAttribute_math_expr(
      CEQL_QUERYParser::Attribute_math_exprContext* ctx) override {
    value = std::make_unique<Attribute>(ctx->getText());
    return {};
  }

  virtual std::any visitUnary_math_expr(
      CEQL_QUERYParser::Unary_math_exprContext* ctx) override {
    visit(ctx->math_expr());
    if (ctx->MINUS()) {
      value = std::make_unique<Negation>(std::move(value));
    }
    return {};
  }

  virtual std::any visitMul_math_expr(
      CEQL_QUERYParser::Mul_math_exprContext* ctx) override {
    visit(ctx->math_expr()[0]);
    std::unique_ptr<Value> first_val = std::move(value);
    visit(ctx->math_expr()[1]);
    if (ctx->STAR()) {
      value = std::make_unique<Multiplication>(std::move(first_val),
                                               std::move(value));
    } else if (ctx->SLASH()) {
      value = std::make_unique<Division>(std::move(first_val),
                                         std::move(value));
    } else {
      value =
          std::make_unique<Modulo>(std::move(first_val), std::move(value));
    }
    return {};
  }

  virtual std::any visitSum_math_expr(
      CEQL_QUERYParser::Sum_math_exprContext* ctx) override {
    visit(ctx->math_expr()[0]);
    std::unique_ptr<Value> first_val = std::move(value);
    visit(ctx->math_expr()[1]);
    if (ctx->PLUS()) {
      value = std::make_unique<Addition>(std::move(first_val),
                                         std::move(value));
    } else {
      value = std::make_unique<Subtraction>(std::move(first_val),
                                            std::move(value));
    }
    return {};
  }

  virtual std::any visitString(
      CEQL_QUERYParser::StringContext* ctx) override {
    value = std::make_unique<StringLiteral>(ctx->getText());
    return {};
  }

  virtual std::any visitAttribute_name(
      CEQL_QUERYParser::Attribute_nameContext* ctx) override {
    value = std::make_unique<Attribute>(ctx->getText());
    return {};
  }

  virtual std::any visitInteger_range(
      CEQL_QUERYParser::Integer_rangeContext* ctx) override {
    int64_t first_int = std::stoll(ctx->integer()[0]->getText());
    int64_t second_int = std::stoll(ctx->integer()[1]->getText());
    value = std::make_unique<Sequence>(
        std::make_unique<IntegerLiteral>(first_int),
        std::make_unique<IntegerLiteral>(second_int));
    return {};
  }

  virtual std::any visitDouble_range(
      CEQL_QUERYParser::Double_rangeContext* ctx) override {
    double first_double = std::stod(ctx->double_()[0]->getText());
    double second_double = std::stod(ctx->double_()[1]->getText());
    value = std::make_unique<Sequence>(
        std::make_unique<DoubleLiteral>(first_double),
        std::make_unique<DoubleLiteral>(second_double));
    return {};
  }

  virtual std::any visitNumber_list(
      CEQL_QUERYParser::Number_listContext* ctx) override {
    std::vector<std::unique_ptr<Value>> values;
    auto numbers = ctx->number();
    for (auto& num_ctx : numbers) {
      visit(num_ctx);
      values.push_back(std::move(value));
    }
    value = std::make_unique<Sequence>(std::move(values));
    return {};
  }

  virtual std::any visitNumber_range_lower(
      CEQL_QUERYParser::Number_range_lowerContext* ctx) override {
    visit(ctx->number());
    value = std::make_unique<Sequence>(std::move(value),
                                       Sequence::LOWER_BOUND);
    return {};
  }

  virtual std::any visitNumber_range_upper(
      CEQL_QUERYParser::Number_range_upperContext* ctx) override {
    visit(ctx->number());
    value = std::make_unique<Sequence>(std::move(value),
                                       Sequence::UPPER_BOUND);
    return {};
  }

  virtual std::any visitString_seq(
      CEQL_QUERYParser::String_seqContext* ctx) override {
    std::vector<std::unique_ptr<Value>> values;
    auto strings = ctx->string();
    for (auto& string_ctx : strings) {
      visit(string_ctx);
      values.push_back(std::move(value));
    }
    value = std::make_unique<Sequence>(std::move(values));
    return {};
  }
};
}  // namespace InternalCORECEQLParsing
