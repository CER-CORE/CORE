
// Generated from CEQLQueryLexer.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  CEQLQueryLexer : public antlr4::Lexer {
public:
  enum {
    K_ALL = 1, K_AND = 2, K_ANY = 3, K_AS = 4, K_BY = 5, K_CONSUME = 6, 
    K_LIMIT = 7, K_DISTINCT = 8, K_EVENT = 9, K_EVENTS = 10, K_FILTER = 11, 
    K_FROM = 12, K_HOURS = 13, K_IN = 14, K_LAST = 15, K_LIKE = 16, K_MAX = 17, 
    K_MINUTES = 18, K_NEXT = 19, K_NONE = 20, K_NOT = 21, K_OR = 22, K_PARTITION = 23, 
    K_RANGE = 24, K_SECONDS = 25, K_SELECT = 26, K_STREAM = 27, K_STRICT = 28, 
    K_UNLESS = 29, K_WHERE = 30, K_WITHIN = 31, PERCENT = 32, PLUS = 33, 
    MINUS = 34, STAR = 35, SLASH = 36, LE = 37, LEQ = 38, GE = 39, GEQ = 40, 
    EQ = 41, NEQ = 42, SEMICOLON = 43, COLON = 44, COMMA = 45, DOUBLE_DOT = 46, 
    LEFT_PARENTHESIS = 47, RIGHT_PARENTHESIS = 48, LEFT_SQUARE_BRACKET = 49, 
    RIGHT_SQUARE_BRACKET = 50, LEFT_CURLY_BRACKET = 51, RIGHT_CURLY_BRACKET = 52, 
    COLON_PLUS = 53, IDENTIFIER = 54, DOUBLE_LITERAL = 55, INTEGER_LITERAL = 56, 
    NUMERICAL_EXPONENT = 57, STRING_LITERAL = 58, SINGLE_LINE_COMMENT = 59, 
    MULTILINE_COMMENT = 60, SPACES = 61, UNEXPECTED_CHAR = 62, REGEX_START = 63, 
    REGEX_END = 64, REGEX_END_ESCAPED = 65, REGEX_PIPE = 66, REGEX_EXCLAMAITON = 67, 
    REGEX_L_CURLY = 68, REGEX_R_CURLY = 69, REGEX_L_PAR = 70, REGEX_R_PAR = 71, 
    REGEX_COMMA = 72, REGEX_QUESTION = 73, REGEX_PLUS = 74, REGEX_STAR = 75, 
    REGEX_HAT = 76, REGEX_HYPHEN = 77, REGEX_L_BRACK = 78, REGEX_R_BRACK = 79, 
    REGEX_BACKSLASH = 80, REGEX_ALPHA = 81, REGEX_DOT = 82, REGEX_DOUBLED_DOT = 83, 
    UNRECOGNIZED = 84, REGEX_DECIMAL_DIGIT = 85, REGEX_NOT_DECIMAL_DIGIT = 86, 
    REGEX_WHITESPACE = 87, REGEX_NOT_WHITESPACE = 88, REGEX_ALPHANUMERIC = 89, 
    REGEX_NOT_ALPHANUMERIC = 90, REGEX_DIGIT = 91
  };

  enum {
    REGEX = 1
  };

  explicit CEQLQueryLexer(antlr4::CharStream *input);

  ~CEQLQueryLexer() override;


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

