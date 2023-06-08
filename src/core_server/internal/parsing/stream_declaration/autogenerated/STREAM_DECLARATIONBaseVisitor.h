
// Generated from STREAM_DECLARATION.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "STREAM_DECLARATIONVisitor.h"


/**
 * This class provides an empty implementation of STREAM_DECLARATIONVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  STREAM_DECLARATIONBaseVisitor : public STREAM_DECLARATIONVisitor {
public:

  virtual std::any visitParse(STREAM_DECLARATIONParser::ParseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitError(STREAM_DECLARATIONParser::ErrorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCore_stmt(STREAM_DECLARATIONParser::Core_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCore_declaration(STREAM_DECLARATIONParser::Core_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_declaration(STREAM_DECLARATIONParser::Event_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_dec_list(STREAM_DECLARATIONParser::Attribute_dec_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_declaration(STREAM_DECLARATIONParser::Attribute_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDatatype(STREAM_DECLARATIONParser::DatatypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStream_declaration(STREAM_DECLARATIONParser::Stream_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_list(STREAM_DECLARATIONParser::Event_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCore_query(STREAM_DECLARATIONParser::Core_queryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSs_all(STREAM_DECLARATIONParser::Ss_allContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSs_any(STREAM_DECLARATIONParser::Ss_anyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSs_last(STREAM_DECLARATIONParser::Ss_lastContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSs_max(STREAM_DECLARATIONParser::Ss_maxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSs_next(STREAM_DECLARATIONParser::Ss_nextContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSs_strict(STREAM_DECLARATIONParser::Ss_strictContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitResult_values(STREAM_DECLARATIONParser::Result_valuesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_core_pattern(STREAM_DECLARATIONParser::Event_core_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKleene_core_pattern(STREAM_DECLARATIONParser::Kleene_core_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_core_pattern(STREAM_DECLARATIONParser::Assign_core_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_core_pattern(STREAM_DECLARATIONParser::Binary_core_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPar_core_pattern(STREAM_DECLARATIONParser::Par_core_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter_core_pattern(STREAM_DECLARATIONParser::Filter_core_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPartition_list(STREAM_DECLARATIONParser::Partition_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_list(STREAM_DECLARATIONParser::Attribute_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCp_any(STREAM_DECLARATIONParser::Cp_anyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCp_partition(STREAM_DECLARATIONParser::Cp_partitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCp_none(STREAM_DECLARATIONParser::Cp_noneContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPar_filter(STREAM_DECLARATIONParser::Par_filterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnd_filter(STREAM_DECLARATIONParser::And_filterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_filter(STREAM_DECLARATIONParser::Event_filterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOr_filter(STREAM_DECLARATIONParser::Or_filterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNot_expr(STREAM_DECLARATIONParser::Not_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEquality_string_expr(STREAM_DECLARATIONParser::Equality_string_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnd_expr(STREAM_DECLARATIONParser::And_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPar_bool_expr(STREAM_DECLARATIONParser::Par_bool_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContainment_expr(STREAM_DECLARATIONParser::Containment_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInequality_expr(STREAM_DECLARATIONParser::Inequality_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOr_expr(STREAM_DECLARATIONParser::Or_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEquality_math_expr(STREAM_DECLARATIONParser::Equality_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRegex_expr(STREAM_DECLARATIONParser::Regex_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString_literal(STREAM_DECLARATIONParser::String_literalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString_literal_or_regexp(STREAM_DECLARATIONParser::String_literal_or_regexpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMul_math_expr(STREAM_DECLARATIONParser::Mul_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSum_math_expr(STREAM_DECLARATIONParser::Sum_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_math_expr(STREAM_DECLARATIONParser::Number_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_math_expr(STREAM_DECLARATIONParser::Unary_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_math_expr(STREAM_DECLARATIONParser::Attribute_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPar_math_expr(STREAM_DECLARATIONParser::Par_math_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue_seq(STREAM_DECLARATIONParser::Value_seqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_list(STREAM_DECLARATIONParser::Number_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_range(STREAM_DECLARATIONParser::Number_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_range_lower(STREAM_DECLARATIONParser::Number_range_lowerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber_range_upper(STREAM_DECLARATIONParser::Number_range_upperContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString_seq(STREAM_DECLARATIONParser::String_seqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTime_window(STREAM_DECLARATIONParser::Time_windowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_span(STREAM_DECLARATIONParser::Event_spanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTime_span(STREAM_DECLARATIONParser::Time_spanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHour_span(STREAM_DECLARATIONParser::Hour_spanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMinute_span(STREAM_DECLARATIONParser::Minute_spanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSecond_span(STREAM_DECLARATIONParser::Second_spanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustom_span(STREAM_DECLARATIONParser::Custom_spanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_event(STREAM_DECLARATIONParser::Named_eventContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitS_event_name(STREAM_DECLARATIONParser::S_event_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_name(STREAM_DECLARATIONParser::Event_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStream_name(STREAM_DECLARATIONParser::Stream_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_name(STREAM_DECLARATIONParser::Attribute_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInteger(STREAM_DECLARATIONParser::IntegerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(STREAM_DECLARATIONParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString(STREAM_DECLARATIONParser::StringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAny_name(STREAM_DECLARATIONParser::Any_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyword(STREAM_DECLARATIONParser::KeywordContext *ctx) override {
    return visitChildren(ctx);
  }


};

