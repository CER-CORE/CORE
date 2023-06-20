
// Generated from StreamDeclarationLexer.g4 by ANTLR 4.12.0


#include "StreamDeclarationLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct StreamDeclarationLexerStaticData final {
  StreamDeclarationLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  StreamDeclarationLexerStaticData(const StreamDeclarationLexerStaticData&) = delete;
  StreamDeclarationLexerStaticData(StreamDeclarationLexerStaticData&&) = delete;
  StreamDeclarationLexerStaticData& operator=(const StreamDeclarationLexerStaticData&) = delete;
  StreamDeclarationLexerStaticData& operator=(StreamDeclarationLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag streamdeclarationlexerLexerOnceFlag;
StreamDeclarationLexerStaticData *streamdeclarationlexerLexerStaticData = nullptr;

void streamdeclarationlexerLexerInitialize() {
  assert(streamdeclarationlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<StreamDeclarationLexerStaticData>(
    std::vector<std::string>{
      "K_ALL", "K_AND", "K_ANY", "K_AS", "K_BY", "K_CONSUME", "K_DECLARE", 
      "K_DISTINCT", "K_EVENT", "K_EVENTS", "K_FILTER", "K_FROM", "K_HOURS", 
      "K_IN", "K_LAST", "K_LIKE", "K_MAX", "K_MINUTES", "K_NEXT", "K_NONE", 
      "K_NOT", "K_OR", "K_PARTITION", "K_SECONDS", "K_SELECT", "K_STREAM", 
      "K_STRICT", "K_UNLESS", "K_WHERE", "K_WITHIN", "PERCENT", "PLUS", 
      "MINUS", "STAR", "SLASH", "LE", "LEQ", "GE", "GEQ", "EQ", "NEQ", "SEMICOLON", 
      "IDENTIFIER", "FLOAT_LITERAL", "INTEGER_LITERAL", "NUMERICAL_EXPONENT", 
      "STRING_LITERAL", "REGEXP", "SINGLE_LINE_COMMENT", "MULTILINE_COMMENT", 
      "SPACES", "UNEXPECTED_CHAR", "DIGIT", "A", "B", "C", "D", "E", "F", 
      "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", 
      "U", "V", "W", "X", "Y", "Z"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "'%'", "'+'", 
      "'-'", "'*'", "'/'", "'<'", "'<='", "'>'", "'>='", "", "", "';'"
    },
    std::vector<std::string>{
      "", "K_ALL", "K_AND", "K_ANY", "K_AS", "K_BY", "K_CONSUME", "K_DECLARE", 
      "K_DISTINCT", "K_EVENT", "K_EVENTS", "K_FILTER", "K_FROM", "K_HOURS", 
      "K_IN", "K_LAST", "K_LIKE", "K_MAX", "K_MINUTES", "K_NEXT", "K_NONE", 
      "K_NOT", "K_OR", "K_PARTITION", "K_SECONDS", "K_SELECT", "K_STREAM", 
      "K_STRICT", "K_UNLESS", "K_WHERE", "K_WITHIN", "PERCENT", "PLUS", 
      "MINUS", "STAR", "SLASH", "LE", "LEQ", "GE", "GEQ", "EQ", "NEQ", "SEMICOLON", 
      "IDENTIFIER", "FLOAT_LITERAL", "INTEGER_LITERAL", "NUMERICAL_EXPONENT", 
      "STRING_LITERAL", "REGEXP", "SINGLE_LINE_COMMENT", "MULTILINE_COMMENT", 
      "SPACES", "UNEXPECTED_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,52,529,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,
  	7,70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,
  	7,77,2,78,7,78,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,
  	3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,
  	1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,3,12,233,8,12,1,13,1,13,
  	1,13,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,
  	1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,259,8,17,1,18,1,18,1,18,
  	1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,3,23,295,8,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,25,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,33,1,33,1,34,
  	1,34,1,35,1,35,1,36,1,36,1,36,1,37,1,37,1,38,1,38,1,38,1,39,1,39,1,39,
  	3,39,361,8,39,1,40,1,40,1,40,1,40,3,40,367,8,40,1,41,1,41,1,42,1,42,1,
  	42,1,42,5,42,375,8,42,10,42,12,42,378,9,42,1,42,1,42,1,42,5,42,383,8,
  	42,10,42,12,42,386,9,42,3,42,388,8,42,1,43,1,43,1,43,1,43,1,43,3,43,395,
  	8,43,1,43,1,43,4,43,399,8,43,11,43,12,43,400,1,43,3,43,404,8,43,1,43,
  	1,43,4,43,408,8,43,11,43,12,43,409,1,43,1,43,3,43,414,8,43,1,44,4,44,
  	417,8,44,11,44,12,44,418,1,45,1,45,3,45,423,8,45,1,45,4,45,426,8,45,11,
  	45,12,45,427,1,46,1,46,1,46,1,46,5,46,434,8,46,10,46,12,46,437,9,46,1,
  	46,1,46,1,47,1,47,1,48,1,48,1,48,1,48,5,48,447,8,48,10,48,12,48,450,9,
  	48,1,48,1,48,1,49,1,49,1,49,1,49,5,49,458,8,49,10,49,12,49,461,9,49,1,
  	49,1,49,1,49,3,49,466,8,49,1,49,1,49,1,50,1,50,1,50,1,50,1,51,1,51,1,
  	52,1,52,1,53,1,53,1,54,1,54,1,55,1,55,1,56,1,56,1,57,1,57,1,58,1,58,1,
  	59,1,59,1,60,1,60,1,61,1,61,1,62,1,62,1,63,1,63,1,64,1,64,1,65,1,65,1,
  	66,1,66,1,67,1,67,1,68,1,68,1,69,1,69,1,70,1,70,1,71,1,71,1,72,1,72,1,
  	73,1,73,1,74,1,74,1,75,1,75,1,76,1,76,1,77,1,77,1,78,1,78,1,459,0,79,
  	1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,
  	29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,
  	26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,
  	75,38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,
  	49,99,50,101,51,103,52,105,0,107,0,109,0,111,0,113,0,115,0,117,0,119,
  	0,121,0,123,0,125,0,127,0,129,0,131,0,133,0,135,0,137,0,139,0,141,0,143,
  	0,145,0,147,0,149,0,151,0,153,0,155,0,157,0,1,0,33,1,0,96,96,3,0,65,90,
  	95,95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,39,39,2,0,10,10,13,13,3,
  	0,9,11,13,13,32,32,1,0,48,57,2,0,65,65,97,97,2,0,66,66,98,98,2,0,67,67,
  	99,99,2,0,68,68,100,100,2,0,69,69,101,101,2,0,70,70,102,102,2,0,71,71,
  	103,103,2,0,72,72,104,104,2,0,73,73,105,105,2,0,74,74,106,106,2,0,75,
  	75,107,107,2,0,76,76,108,108,2,0,77,77,109,109,2,0,78,78,110,110,2,0,
  	79,79,111,111,2,0,80,80,112,112,2,0,81,81,113,113,2,0,82,82,114,114,2,
  	0,83,83,115,115,2,0,84,84,116,116,2,0,85,85,117,117,2,0,86,86,118,118,
  	2,0,87,87,119,119,2,0,88,88,120,120,2,0,89,89,121,121,2,0,90,90,122,122,
  	524,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,
  	1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,
  	0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,
  	0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,
  	1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,
  	0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,
  	0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,
  	1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,
  	0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,
  	0,97,1,0,0,0,0,99,1,0,0,0,0,101,1,0,0,0,0,103,1,0,0,0,1,159,1,0,0,0,3,
  	163,1,0,0,0,5,167,1,0,0,0,7,171,1,0,0,0,9,174,1,0,0,0,11,177,1,0,0,0,
  	13,185,1,0,0,0,15,193,1,0,0,0,17,202,1,0,0,0,19,208,1,0,0,0,21,215,1,
  	0,0,0,23,222,1,0,0,0,25,227,1,0,0,0,27,234,1,0,0,0,29,237,1,0,0,0,31,
  	242,1,0,0,0,33,247,1,0,0,0,35,251,1,0,0,0,37,260,1,0,0,0,39,265,1,0,0,
  	0,41,270,1,0,0,0,43,274,1,0,0,0,45,277,1,0,0,0,47,287,1,0,0,0,49,296,
  	1,0,0,0,51,303,1,0,0,0,53,310,1,0,0,0,55,317,1,0,0,0,57,324,1,0,0,0,59,
  	330,1,0,0,0,61,337,1,0,0,0,63,339,1,0,0,0,65,341,1,0,0,0,67,343,1,0,0,
  	0,69,345,1,0,0,0,71,347,1,0,0,0,73,349,1,0,0,0,75,352,1,0,0,0,77,354,
  	1,0,0,0,79,360,1,0,0,0,81,366,1,0,0,0,83,368,1,0,0,0,85,387,1,0,0,0,87,
  	413,1,0,0,0,89,416,1,0,0,0,91,420,1,0,0,0,93,429,1,0,0,0,95,440,1,0,0,
  	0,97,442,1,0,0,0,99,453,1,0,0,0,101,469,1,0,0,0,103,473,1,0,0,0,105,475,
  	1,0,0,0,107,477,1,0,0,0,109,479,1,0,0,0,111,481,1,0,0,0,113,483,1,0,0,
  	0,115,485,1,0,0,0,117,487,1,0,0,0,119,489,1,0,0,0,121,491,1,0,0,0,123,
  	493,1,0,0,0,125,495,1,0,0,0,127,497,1,0,0,0,129,499,1,0,0,0,131,501,1,
  	0,0,0,133,503,1,0,0,0,135,505,1,0,0,0,137,507,1,0,0,0,139,509,1,0,0,0,
  	141,511,1,0,0,0,143,513,1,0,0,0,145,515,1,0,0,0,147,517,1,0,0,0,149,519,
  	1,0,0,0,151,521,1,0,0,0,153,523,1,0,0,0,155,525,1,0,0,0,157,527,1,0,0,
  	0,159,160,3,107,53,0,160,161,3,129,64,0,161,162,3,129,64,0,162,2,1,0,
  	0,0,163,164,3,107,53,0,164,165,3,133,66,0,165,166,3,113,56,0,166,4,1,
  	0,0,0,167,168,3,107,53,0,168,169,3,133,66,0,169,170,3,155,77,0,170,6,
  	1,0,0,0,171,172,3,107,53,0,172,173,3,143,71,0,173,8,1,0,0,0,174,175,3,
  	109,54,0,175,176,3,155,77,0,176,10,1,0,0,0,177,178,3,111,55,0,178,179,
  	3,135,67,0,179,180,3,133,66,0,180,181,3,143,71,0,181,182,3,147,73,0,182,
  	183,3,131,65,0,183,184,3,115,57,0,184,12,1,0,0,0,185,186,3,113,56,0,186,
  	187,3,115,57,0,187,188,3,111,55,0,188,189,3,129,64,0,189,190,3,107,53,
  	0,190,191,3,141,70,0,191,192,3,115,57,0,192,14,1,0,0,0,193,194,3,113,
  	56,0,194,195,3,123,61,0,195,196,3,143,71,0,196,197,3,145,72,0,197,198,
  	3,123,61,0,198,199,3,133,66,0,199,200,3,111,55,0,200,201,3,145,72,0,201,
  	16,1,0,0,0,202,203,3,115,57,0,203,204,3,149,74,0,204,205,3,115,57,0,205,
  	206,3,133,66,0,206,207,3,145,72,0,207,18,1,0,0,0,208,209,3,115,57,0,209,
  	210,3,149,74,0,210,211,3,115,57,0,211,212,3,133,66,0,212,213,3,145,72,
  	0,213,214,3,143,71,0,214,20,1,0,0,0,215,216,3,117,58,0,216,217,3,123,
  	61,0,217,218,3,129,64,0,218,219,3,145,72,0,219,220,3,115,57,0,220,221,
  	3,141,70,0,221,22,1,0,0,0,222,223,3,117,58,0,223,224,3,141,70,0,224,225,
  	3,135,67,0,225,226,3,131,65,0,226,24,1,0,0,0,227,228,3,121,60,0,228,229,
  	3,135,67,0,229,230,3,147,73,0,230,232,3,141,70,0,231,233,3,143,71,0,232,
  	231,1,0,0,0,232,233,1,0,0,0,233,26,1,0,0,0,234,235,3,123,61,0,235,236,
  	3,133,66,0,236,28,1,0,0,0,237,238,3,129,64,0,238,239,3,107,53,0,239,240,
  	3,143,71,0,240,241,3,145,72,0,241,30,1,0,0,0,242,243,3,129,64,0,243,244,
  	3,123,61,0,244,245,3,127,63,0,245,246,3,115,57,0,246,32,1,0,0,0,247,248,
  	3,131,65,0,248,249,3,107,53,0,249,250,3,153,76,0,250,34,1,0,0,0,251,252,
  	3,131,65,0,252,253,3,123,61,0,253,254,3,133,66,0,254,255,3,147,73,0,255,
  	256,3,145,72,0,256,258,3,115,57,0,257,259,3,143,71,0,258,257,1,0,0,0,
  	258,259,1,0,0,0,259,36,1,0,0,0,260,261,3,133,66,0,261,262,3,115,57,0,
  	262,263,3,153,76,0,263,264,3,145,72,0,264,38,1,0,0,0,265,266,3,133,66,
  	0,266,267,3,135,67,0,267,268,3,133,66,0,268,269,3,115,57,0,269,40,1,0,
  	0,0,270,271,3,133,66,0,271,272,3,135,67,0,272,273,3,145,72,0,273,42,1,
  	0,0,0,274,275,3,135,67,0,275,276,3,141,70,0,276,44,1,0,0,0,277,278,3,
  	137,68,0,278,279,3,107,53,0,279,280,3,141,70,0,280,281,3,145,72,0,281,
  	282,3,123,61,0,282,283,3,145,72,0,283,284,3,123,61,0,284,285,3,135,67,
  	0,285,286,3,133,66,0,286,46,1,0,0,0,287,288,3,143,71,0,288,289,3,115,
  	57,0,289,290,3,111,55,0,290,291,3,135,67,0,291,292,3,133,66,0,292,294,
  	3,113,56,0,293,295,3,143,71,0,294,293,1,0,0,0,294,295,1,0,0,0,295,48,
  	1,0,0,0,296,297,3,143,71,0,297,298,3,115,57,0,298,299,3,129,64,0,299,
  	300,3,115,57,0,300,301,3,111,55,0,301,302,3,145,72,0,302,50,1,0,0,0,303,
  	304,3,143,71,0,304,305,3,145,72,0,305,306,3,141,70,0,306,307,3,115,57,
  	0,307,308,3,107,53,0,308,309,3,131,65,0,309,52,1,0,0,0,310,311,3,143,
  	71,0,311,312,3,145,72,0,312,313,3,141,70,0,313,314,3,123,61,0,314,315,
  	3,111,55,0,315,316,3,145,72,0,316,54,1,0,0,0,317,318,3,147,73,0,318,319,
  	3,133,66,0,319,320,3,129,64,0,320,321,3,115,57,0,321,322,3,143,71,0,322,
  	323,3,143,71,0,323,56,1,0,0,0,324,325,3,151,75,0,325,326,3,121,60,0,326,
  	327,3,115,57,0,327,328,3,141,70,0,328,329,3,115,57,0,329,58,1,0,0,0,330,
  	331,3,151,75,0,331,332,3,123,61,0,332,333,3,145,72,0,333,334,3,121,60,
  	0,334,335,3,123,61,0,335,336,3,133,66,0,336,60,1,0,0,0,337,338,5,37,0,
  	0,338,62,1,0,0,0,339,340,5,43,0,0,340,64,1,0,0,0,341,342,5,45,0,0,342,
  	66,1,0,0,0,343,344,5,42,0,0,344,68,1,0,0,0,345,346,5,47,0,0,346,70,1,
  	0,0,0,347,348,5,60,0,0,348,72,1,0,0,0,349,350,5,60,0,0,350,351,5,61,0,
  	0,351,74,1,0,0,0,352,353,5,62,0,0,353,76,1,0,0,0,354,355,5,62,0,0,355,
  	356,5,61,0,0,356,78,1,0,0,0,357,358,5,61,0,0,358,361,5,61,0,0,359,361,
  	5,61,0,0,360,357,1,0,0,0,360,359,1,0,0,0,361,80,1,0,0,0,362,363,5,33,
  	0,0,363,367,5,61,0,0,364,365,5,60,0,0,365,367,5,62,0,0,366,362,1,0,0,
  	0,366,364,1,0,0,0,367,82,1,0,0,0,368,369,5,59,0,0,369,84,1,0,0,0,370,
  	376,5,96,0,0,371,375,8,0,0,0,372,373,5,96,0,0,373,375,5,96,0,0,374,371,
  	1,0,0,0,374,372,1,0,0,0,375,378,1,0,0,0,376,374,1,0,0,0,376,377,1,0,0,
  	0,377,379,1,0,0,0,378,376,1,0,0,0,379,388,5,96,0,0,380,384,7,1,0,0,381,
  	383,7,2,0,0,382,381,1,0,0,0,383,386,1,0,0,0,384,382,1,0,0,0,384,385,1,
  	0,0,0,385,388,1,0,0,0,386,384,1,0,0,0,387,370,1,0,0,0,387,380,1,0,0,0,
  	388,86,1,0,0,0,389,390,3,89,44,0,390,391,5,46,0,0,391,392,3,91,45,0,392,
  	414,1,0,0,0,393,395,3,89,44,0,394,393,1,0,0,0,394,395,1,0,0,0,395,396,
  	1,0,0,0,396,398,5,46,0,0,397,399,3,105,52,0,398,397,1,0,0,0,399,400,1,
  	0,0,0,400,398,1,0,0,0,400,401,1,0,0,0,401,414,1,0,0,0,402,404,3,89,44,
  	0,403,402,1,0,0,0,403,404,1,0,0,0,404,405,1,0,0,0,405,407,5,46,0,0,406,
  	408,3,105,52,0,407,406,1,0,0,0,408,409,1,0,0,0,409,407,1,0,0,0,409,410,
  	1,0,0,0,410,411,1,0,0,0,411,412,3,91,45,0,412,414,1,0,0,0,413,389,1,0,
  	0,0,413,394,1,0,0,0,413,403,1,0,0,0,414,88,1,0,0,0,415,417,3,105,52,0,
  	416,415,1,0,0,0,417,418,1,0,0,0,418,416,1,0,0,0,418,419,1,0,0,0,419,90,
  	1,0,0,0,420,422,3,115,57,0,421,423,5,45,0,0,422,421,1,0,0,0,422,423,1,
  	0,0,0,423,425,1,0,0,0,424,426,3,105,52,0,425,424,1,0,0,0,426,427,1,0,
  	0,0,427,425,1,0,0,0,427,428,1,0,0,0,428,92,1,0,0,0,429,435,5,39,0,0,430,
  	434,8,3,0,0,431,432,5,39,0,0,432,434,5,39,0,0,433,430,1,0,0,0,433,431,
  	1,0,0,0,434,437,1,0,0,0,435,433,1,0,0,0,435,436,1,0,0,0,436,438,1,0,0,
  	0,437,435,1,0,0,0,438,439,5,39,0,0,439,94,1,0,0,0,440,441,3,93,46,0,441,
  	96,1,0,0,0,442,443,5,45,0,0,443,444,5,45,0,0,444,448,1,0,0,0,445,447,
  	8,4,0,0,446,445,1,0,0,0,447,450,1,0,0,0,448,446,1,0,0,0,448,449,1,0,0,
  	0,449,451,1,0,0,0,450,448,1,0,0,0,451,452,6,48,0,0,452,98,1,0,0,0,453,
  	454,5,47,0,0,454,455,5,42,0,0,455,459,1,0,0,0,456,458,9,0,0,0,457,456,
  	1,0,0,0,458,461,1,0,0,0,459,460,1,0,0,0,459,457,1,0,0,0,460,465,1,0,0,
  	0,461,459,1,0,0,0,462,463,5,42,0,0,463,466,5,47,0,0,464,466,5,0,0,1,465,
  	462,1,0,0,0,465,464,1,0,0,0,466,467,1,0,0,0,467,468,6,49,0,0,468,100,
  	1,0,0,0,469,470,7,5,0,0,470,471,1,0,0,0,471,472,6,50,0,0,472,102,1,0,
  	0,0,473,474,9,0,0,0,474,104,1,0,0,0,475,476,7,6,0,0,476,106,1,0,0,0,477,
  	478,7,7,0,0,478,108,1,0,0,0,479,480,7,8,0,0,480,110,1,0,0,0,481,482,7,
  	9,0,0,482,112,1,0,0,0,483,484,7,10,0,0,484,114,1,0,0,0,485,486,7,11,0,
  	0,486,116,1,0,0,0,487,488,7,12,0,0,488,118,1,0,0,0,489,490,7,13,0,0,490,
  	120,1,0,0,0,491,492,7,14,0,0,492,122,1,0,0,0,493,494,7,15,0,0,494,124,
  	1,0,0,0,495,496,7,16,0,0,496,126,1,0,0,0,497,498,7,17,0,0,498,128,1,0,
  	0,0,499,500,7,18,0,0,500,130,1,0,0,0,501,502,7,19,0,0,502,132,1,0,0,0,
  	503,504,7,20,0,0,504,134,1,0,0,0,505,506,7,21,0,0,506,136,1,0,0,0,507,
  	508,7,22,0,0,508,138,1,0,0,0,509,510,7,23,0,0,510,140,1,0,0,0,511,512,
  	7,24,0,0,512,142,1,0,0,0,513,514,7,25,0,0,514,144,1,0,0,0,515,516,7,26,
  	0,0,516,146,1,0,0,0,517,518,7,27,0,0,518,148,1,0,0,0,519,520,7,28,0,0,
  	520,150,1,0,0,0,521,522,7,29,0,0,522,152,1,0,0,0,523,524,7,30,0,0,524,
  	154,1,0,0,0,525,526,7,31,0,0,526,156,1,0,0,0,527,528,7,32,0,0,528,158,
  	1,0,0,0,23,0,232,258,294,360,366,374,376,384,387,394,400,403,409,413,
  	418,422,427,433,435,448,459,465,1,0,1,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  streamdeclarationlexerLexerStaticData = staticData.release();
}

}

StreamDeclarationLexer::StreamDeclarationLexer(CharStream *input) : Lexer(input) {
  StreamDeclarationLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *streamdeclarationlexerLexerStaticData->atn, streamdeclarationlexerLexerStaticData->decisionToDFA, streamdeclarationlexerLexerStaticData->sharedContextCache);
}

StreamDeclarationLexer::~StreamDeclarationLexer() {
  delete _interpreter;
}

std::string StreamDeclarationLexer::getGrammarFileName() const {
  return "StreamDeclarationLexer.g4";
}

const std::vector<std::string>& StreamDeclarationLexer::getRuleNames() const {
  return streamdeclarationlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& StreamDeclarationLexer::getChannelNames() const {
  return streamdeclarationlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& StreamDeclarationLexer::getModeNames() const {
  return streamdeclarationlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& StreamDeclarationLexer::getVocabulary() const {
  return streamdeclarationlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView StreamDeclarationLexer::getSerializedATN() const {
  return streamdeclarationlexerLexerStaticData->serializedATN;
}

const atn::ATN& StreamDeclarationLexer::getATN() const {
  return *streamdeclarationlexerLexerStaticData->atn;
}




void StreamDeclarationLexer::initialize() {
  ::antlr4::internal::call_once(streamdeclarationlexerLexerOnceFlag, streamdeclarationlexerLexerInitialize);
}
