
// Generated from StreamDeclarationLexer.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  StreamDeclarationLexer : public antlr4::Lexer {
public:
  enum {
    K_ALL = 1, K_AND = 2, K_ANY = 3, K_AS = 4, K_BY = 5, K_CONSUME = 6, 
    K_DECLARE = 7, K_DISTINCT = 8, K_EVENT = 9, K_EVENTS = 10, K_FILTER = 11, 
    K_FROM = 12, K_HOURS = 13, K_IN = 14, K_LAST = 15, K_LIKE = 16, K_MAX = 17, 
    K_MINUTES = 18, K_NEXT = 19, K_NONE = 20, K_NOT = 21, K_OR = 22, K_PARTITION = 23, 
    K_SECONDS = 24, K_SELECT = 25, K_STREAM = 26, K_STRICT = 27, K_UNLESS = 28, 
    K_WHERE = 29, K_WITHIN = 30, PERCENT = 31, PLUS = 32, MINUS = 33, STAR = 34, 
    SLASH = 35, LE = 36, LEQ = 37, GE = 38, GEQ = 39, EQ = 40, NEQ = 41, 
    SEMICOLON = 42, IDENTIFIER = 43, FLOAT_LITERAL = 44, INTEGER_LITERAL = 45, 
    NUMERICAL_EXPONENT = 46, STRING_LITERAL = 47, REGEXP = 48, SINGLE_LINE_COMMENT = 49, 
    MULTILINE_COMMENT = 50, SPACES = 51, UNEXPECTED_CHAR = 52
  };

  explicit StreamDeclarationLexer(antlr4::CharStream *input);

  ~StreamDeclarationLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

