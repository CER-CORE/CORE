
// Generated from STREAM_DECLARATION.g4 by ANTLR 4.12.0


#include "STREAM_DECLARATIONLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct STREAM_DECLARATIONLexerStaticData final {
  STREAM_DECLARATIONLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  STREAM_DECLARATIONLexerStaticData(const STREAM_DECLARATIONLexerStaticData&) = delete;
  STREAM_DECLARATIONLexerStaticData(STREAM_DECLARATIONLexerStaticData&&) = delete;
  STREAM_DECLARATIONLexerStaticData& operator=(const STREAM_DECLARATIONLexerStaticData&) = delete;
  STREAM_DECLARATIONLexerStaticData& operator=(STREAM_DECLARATIONLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag stream_declarationlexerLexerOnceFlag;
STREAM_DECLARATIONLexerStaticData *stream_declarationlexerLexerStaticData = nullptr;

void stream_declarationlexerLexerInitialize() {
  assert(stream_declarationlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<STREAM_DECLARATIONLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "K_ALL", "K_AND", "K_ANY", "K_AS", 
      "K_BY", "K_CONSUME", "K_DECLARE", "K_DISTINCT", "K_EVENT", "K_EVENTS", 
      "K_FILTER", "K_FROM", "K_HOURS", "K_IN", "K_LAST", "K_LIKE", "K_MAX", 
      "K_MINUTES", "K_NEXT", "K_NONE", "K_NOT", "K_OR", "K_PARTITION", "K_SECONDS", 
      "K_SELECT", "K_STREAM", "K_STRICT", "K_UNLESS", "K_WHERE", "K_WITHIN", 
      "PERCENT", "PLUS", "MINUS", "STAR", "SLASH", "LE", "LEQ", "GE", "GEQ", 
      "EQ", "NEQ", "SEMICOLON", "IDENTIFIER", "FLOAT_LITERAL", "INTEGER_LITERAL", 
      "NUMERICAL_EXPONENT", "STRING_LITERAL", "REGEXP", "SINGLE_LINE_COMMENT", 
      "MULTILINE_COMMENT", "SPACES", "UNEXPECTED_CHAR", "DIGIT", "A", "B", 
      "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", 
      "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "','", "'int'", "'string'", "'double'", "'long'", 
      "'boolean'", "'['", "']'", "'{'", "'}'", "'..'", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "'%'", "'+'", "'-'", "'*'", "'/'", 
      "'<'", "'<='", "'>'", "'>='", "", "", "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "K_ALL", "K_AND", 
      "K_ANY", "K_AS", "K_BY", "K_CONSUME", "K_DECLARE", "K_DISTINCT", "K_EVENT", 
      "K_EVENTS", "K_FILTER", "K_FROM", "K_HOURS", "K_IN", "K_LAST", "K_LIKE", 
      "K_MAX", "K_MINUTES", "K_NEXT", "K_NONE", "K_NOT", "K_OR", "K_PARTITION", 
      "K_SECONDS", "K_SELECT", "K_STREAM", "K_STRICT", "K_UNLESS", "K_WHERE", 
      "K_WITHIN", "PERCENT", "PLUS", "MINUS", "STAR", "SLASH", "LE", "LEQ", 
      "GE", "GEQ", "EQ", "NEQ", "SEMICOLON", "IDENTIFIER", "FLOAT_LITERAL", 
      "INTEGER_LITERAL", "NUMERICAL_EXPONENT", "STRING_LITERAL", "REGEXP", 
      "SINGLE_LINE_COMMENT", "MULTILINE_COMMENT", "SPACES", "UNEXPECTED_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,65,603,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
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
  	7,77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,
  	7,84,2,85,7,85,2,86,7,86,2,87,7,87,2,88,7,88,2,89,7,89,2,90,7,90,2,91,
  	7,91,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,13,
  	1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,
  	1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,
  	1,25,1,25,3,25,307,8,25,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,28,
  	1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,1,30,
  	1,30,3,30,333,8,30,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,32,
  	1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,35,1,35,
  	1,35,1,35,1,35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,369,8,36,1,37,
  	1,37,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,41,
  	1,41,1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,43,1,43,
  	1,44,1,44,1,45,1,45,1,46,1,46,1,47,1,47,1,48,1,48,1,49,1,49,1,49,1,50,
  	1,50,1,51,1,51,1,51,1,52,1,52,1,52,3,52,435,8,52,1,53,1,53,1,53,1,53,
  	3,53,441,8,53,1,54,1,54,1,55,1,55,1,55,1,55,5,55,449,8,55,10,55,12,55,
  	452,9,55,1,55,1,55,1,55,5,55,457,8,55,10,55,12,55,460,9,55,3,55,462,8,
  	55,1,56,1,56,1,56,1,56,1,56,3,56,469,8,56,1,56,1,56,4,56,473,8,56,11,
  	56,12,56,474,1,56,3,56,478,8,56,1,56,1,56,4,56,482,8,56,11,56,12,56,483,
  	1,56,1,56,3,56,488,8,56,1,57,4,57,491,8,57,11,57,12,57,492,1,58,1,58,
  	3,58,497,8,58,1,58,4,58,500,8,58,11,58,12,58,501,1,59,1,59,1,59,1,59,
  	5,59,508,8,59,10,59,12,59,511,9,59,1,59,1,59,1,60,1,60,1,61,1,61,1,61,
  	1,61,5,61,521,8,61,10,61,12,61,524,9,61,1,61,1,61,1,62,1,62,1,62,1,62,
  	5,62,532,8,62,10,62,12,62,535,9,62,1,62,1,62,1,62,3,62,540,8,62,1,62,
  	1,62,1,63,1,63,1,63,1,63,1,64,1,64,1,65,1,65,1,66,1,66,1,67,1,67,1,68,
  	1,68,1,69,1,69,1,70,1,70,1,71,1,71,1,72,1,72,1,73,1,73,1,74,1,74,1,75,
  	1,75,1,76,1,76,1,77,1,77,1,78,1,78,1,79,1,79,1,80,1,80,1,81,1,81,1,82,
  	1,82,1,83,1,83,1,84,1,84,1,85,1,85,1,86,1,86,1,87,1,87,1,88,1,88,1,89,
  	1,89,1,90,1,90,1,91,1,91,1,533,0,92,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,
  	8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,
  	20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,
  	63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,40,81,41,83,42,85,
  	43,87,44,89,45,91,46,93,47,95,48,97,49,99,50,101,51,103,52,105,53,107,
  	54,109,55,111,56,113,57,115,58,117,59,119,60,121,61,123,62,125,63,127,
  	64,129,65,131,0,133,0,135,0,137,0,139,0,141,0,143,0,145,0,147,0,149,0,
  	151,0,153,0,155,0,157,0,159,0,161,0,163,0,165,0,167,0,169,0,171,0,173,
  	0,175,0,177,0,179,0,181,0,183,0,1,0,33,1,0,96,96,3,0,65,90,95,95,97,122,
  	4,0,48,57,65,90,95,95,97,122,1,0,39,39,2,0,10,10,13,13,3,0,9,11,13,13,
  	32,32,1,0,48,57,2,0,65,65,97,97,2,0,66,66,98,98,2,0,67,67,99,99,2,0,68,
  	68,100,100,2,0,69,69,101,101,2,0,70,70,102,102,2,0,71,71,103,103,2,0,
  	72,72,104,104,2,0,73,73,105,105,2,0,74,74,106,106,2,0,75,75,107,107,2,
  	0,76,76,108,108,2,0,77,77,109,109,2,0,78,78,110,110,2,0,79,79,111,111,
  	2,0,80,80,112,112,2,0,81,81,113,113,2,0,82,82,114,114,2,0,83,83,115,115,
  	2,0,84,84,116,116,2,0,85,85,117,117,2,0,86,86,118,118,2,0,87,87,119,119,
  	2,0,88,88,120,120,2,0,89,89,121,121,2,0,90,90,122,122,598,0,1,1,0,0,0,
  	0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,
  	0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,
  	0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,
  	1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,
  	0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,
  	0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,
  	1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,
  	0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,
  	0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,0,97,1,0,0,0,0,99,
  	1,0,0,0,0,101,1,0,0,0,0,103,1,0,0,0,0,105,1,0,0,0,0,107,1,0,0,0,0,109,
  	1,0,0,0,0,111,1,0,0,0,0,113,1,0,0,0,0,115,1,0,0,0,0,117,1,0,0,0,0,119,
  	1,0,0,0,0,121,1,0,0,0,0,123,1,0,0,0,0,125,1,0,0,0,0,127,1,0,0,0,0,129,
  	1,0,0,0,1,185,1,0,0,0,3,187,1,0,0,0,5,189,1,0,0,0,7,191,1,0,0,0,9,195,
  	1,0,0,0,11,202,1,0,0,0,13,209,1,0,0,0,15,214,1,0,0,0,17,222,1,0,0,0,19,
  	224,1,0,0,0,21,226,1,0,0,0,23,228,1,0,0,0,25,230,1,0,0,0,27,233,1,0,0,
  	0,29,237,1,0,0,0,31,241,1,0,0,0,33,245,1,0,0,0,35,248,1,0,0,0,37,251,
  	1,0,0,0,39,259,1,0,0,0,41,267,1,0,0,0,43,276,1,0,0,0,45,282,1,0,0,0,47,
  	289,1,0,0,0,49,296,1,0,0,0,51,301,1,0,0,0,53,308,1,0,0,0,55,311,1,0,0,
  	0,57,316,1,0,0,0,59,321,1,0,0,0,61,325,1,0,0,0,63,334,1,0,0,0,65,339,
  	1,0,0,0,67,344,1,0,0,0,69,348,1,0,0,0,71,351,1,0,0,0,73,361,1,0,0,0,75,
  	370,1,0,0,0,77,377,1,0,0,0,79,384,1,0,0,0,81,391,1,0,0,0,83,398,1,0,0,
  	0,85,404,1,0,0,0,87,411,1,0,0,0,89,413,1,0,0,0,91,415,1,0,0,0,93,417,
  	1,0,0,0,95,419,1,0,0,0,97,421,1,0,0,0,99,423,1,0,0,0,101,426,1,0,0,0,
  	103,428,1,0,0,0,105,434,1,0,0,0,107,440,1,0,0,0,109,442,1,0,0,0,111,461,
  	1,0,0,0,113,487,1,0,0,0,115,490,1,0,0,0,117,494,1,0,0,0,119,503,1,0,0,
  	0,121,514,1,0,0,0,123,516,1,0,0,0,125,527,1,0,0,0,127,543,1,0,0,0,129,
  	547,1,0,0,0,131,549,1,0,0,0,133,551,1,0,0,0,135,553,1,0,0,0,137,555,1,
  	0,0,0,139,557,1,0,0,0,141,559,1,0,0,0,143,561,1,0,0,0,145,563,1,0,0,0,
  	147,565,1,0,0,0,149,567,1,0,0,0,151,569,1,0,0,0,153,571,1,0,0,0,155,573,
  	1,0,0,0,157,575,1,0,0,0,159,577,1,0,0,0,161,579,1,0,0,0,163,581,1,0,0,
  	0,165,583,1,0,0,0,167,585,1,0,0,0,169,587,1,0,0,0,171,589,1,0,0,0,173,
  	591,1,0,0,0,175,593,1,0,0,0,177,595,1,0,0,0,179,597,1,0,0,0,181,599,1,
  	0,0,0,183,601,1,0,0,0,185,186,5,40,0,0,186,2,1,0,0,0,187,188,5,41,0,0,
  	188,4,1,0,0,0,189,190,5,44,0,0,190,6,1,0,0,0,191,192,5,105,0,0,192,193,
  	5,110,0,0,193,194,5,116,0,0,194,8,1,0,0,0,195,196,5,115,0,0,196,197,5,
  	116,0,0,197,198,5,114,0,0,198,199,5,105,0,0,199,200,5,110,0,0,200,201,
  	5,103,0,0,201,10,1,0,0,0,202,203,5,100,0,0,203,204,5,111,0,0,204,205,
  	5,117,0,0,205,206,5,98,0,0,206,207,5,108,0,0,207,208,5,101,0,0,208,12,
  	1,0,0,0,209,210,5,108,0,0,210,211,5,111,0,0,211,212,5,110,0,0,212,213,
  	5,103,0,0,213,14,1,0,0,0,214,215,5,98,0,0,215,216,5,111,0,0,216,217,5,
  	111,0,0,217,218,5,108,0,0,218,219,5,101,0,0,219,220,5,97,0,0,220,221,
  	5,110,0,0,221,16,1,0,0,0,222,223,5,91,0,0,223,18,1,0,0,0,224,225,5,93,
  	0,0,225,20,1,0,0,0,226,227,5,123,0,0,227,22,1,0,0,0,228,229,5,125,0,0,
  	229,24,1,0,0,0,230,231,5,46,0,0,231,232,5,46,0,0,232,26,1,0,0,0,233,234,
  	3,133,66,0,234,235,3,155,77,0,235,236,3,155,77,0,236,28,1,0,0,0,237,238,
  	3,133,66,0,238,239,3,159,79,0,239,240,3,139,69,0,240,30,1,0,0,0,241,242,
  	3,133,66,0,242,243,3,159,79,0,243,244,3,181,90,0,244,32,1,0,0,0,245,246,
  	3,133,66,0,246,247,3,169,84,0,247,34,1,0,0,0,248,249,3,135,67,0,249,250,
  	3,181,90,0,250,36,1,0,0,0,251,252,3,137,68,0,252,253,3,161,80,0,253,254,
  	3,159,79,0,254,255,3,169,84,0,255,256,3,173,86,0,256,257,3,157,78,0,257,
  	258,3,141,70,0,258,38,1,0,0,0,259,260,3,139,69,0,260,261,3,141,70,0,261,
  	262,3,137,68,0,262,263,3,155,77,0,263,264,3,133,66,0,264,265,3,167,83,
  	0,265,266,3,141,70,0,266,40,1,0,0,0,267,268,3,139,69,0,268,269,3,149,
  	74,0,269,270,3,169,84,0,270,271,3,171,85,0,271,272,3,149,74,0,272,273,
  	3,159,79,0,273,274,3,137,68,0,274,275,3,171,85,0,275,42,1,0,0,0,276,277,
  	3,141,70,0,277,278,3,175,87,0,278,279,3,141,70,0,279,280,3,159,79,0,280,
  	281,3,171,85,0,281,44,1,0,0,0,282,283,3,141,70,0,283,284,3,175,87,0,284,
  	285,3,141,70,0,285,286,3,159,79,0,286,287,3,171,85,0,287,288,3,169,84,
  	0,288,46,1,0,0,0,289,290,3,143,71,0,290,291,3,149,74,0,291,292,3,155,
  	77,0,292,293,3,171,85,0,293,294,3,141,70,0,294,295,3,167,83,0,295,48,
  	1,0,0,0,296,297,3,143,71,0,297,298,3,167,83,0,298,299,3,161,80,0,299,
  	300,3,157,78,0,300,50,1,0,0,0,301,302,3,147,73,0,302,303,3,161,80,0,303,
  	304,3,173,86,0,304,306,3,167,83,0,305,307,3,169,84,0,306,305,1,0,0,0,
  	306,307,1,0,0,0,307,52,1,0,0,0,308,309,3,149,74,0,309,310,3,159,79,0,
  	310,54,1,0,0,0,311,312,3,155,77,0,312,313,3,133,66,0,313,314,3,169,84,
  	0,314,315,3,171,85,0,315,56,1,0,0,0,316,317,3,155,77,0,317,318,3,149,
  	74,0,318,319,3,153,76,0,319,320,3,141,70,0,320,58,1,0,0,0,321,322,3,157,
  	78,0,322,323,3,133,66,0,323,324,3,179,89,0,324,60,1,0,0,0,325,326,3,157,
  	78,0,326,327,3,149,74,0,327,328,3,159,79,0,328,329,3,173,86,0,329,330,
  	3,171,85,0,330,332,3,141,70,0,331,333,3,169,84,0,332,331,1,0,0,0,332,
  	333,1,0,0,0,333,62,1,0,0,0,334,335,3,159,79,0,335,336,3,141,70,0,336,
  	337,3,179,89,0,337,338,3,171,85,0,338,64,1,0,0,0,339,340,3,159,79,0,340,
  	341,3,161,80,0,341,342,3,159,79,0,342,343,3,141,70,0,343,66,1,0,0,0,344,
  	345,3,159,79,0,345,346,3,161,80,0,346,347,3,171,85,0,347,68,1,0,0,0,348,
  	349,3,161,80,0,349,350,3,167,83,0,350,70,1,0,0,0,351,352,3,163,81,0,352,
  	353,3,133,66,0,353,354,3,167,83,0,354,355,3,171,85,0,355,356,3,149,74,
  	0,356,357,3,171,85,0,357,358,3,149,74,0,358,359,3,161,80,0,359,360,3,
  	159,79,0,360,72,1,0,0,0,361,362,3,169,84,0,362,363,3,141,70,0,363,364,
  	3,137,68,0,364,365,3,161,80,0,365,366,3,159,79,0,366,368,3,139,69,0,367,
  	369,3,169,84,0,368,367,1,0,0,0,368,369,1,0,0,0,369,74,1,0,0,0,370,371,
  	3,169,84,0,371,372,3,141,70,0,372,373,3,155,77,0,373,374,3,141,70,0,374,
  	375,3,137,68,0,375,376,3,171,85,0,376,76,1,0,0,0,377,378,3,169,84,0,378,
  	379,3,171,85,0,379,380,3,167,83,0,380,381,3,141,70,0,381,382,3,133,66,
  	0,382,383,3,157,78,0,383,78,1,0,0,0,384,385,3,169,84,0,385,386,3,171,
  	85,0,386,387,3,167,83,0,387,388,3,149,74,0,388,389,3,137,68,0,389,390,
  	3,171,85,0,390,80,1,0,0,0,391,392,3,173,86,0,392,393,3,159,79,0,393,394,
  	3,155,77,0,394,395,3,141,70,0,395,396,3,169,84,0,396,397,3,169,84,0,397,
  	82,1,0,0,0,398,399,3,177,88,0,399,400,3,147,73,0,400,401,3,141,70,0,401,
  	402,3,167,83,0,402,403,3,141,70,0,403,84,1,0,0,0,404,405,3,177,88,0,405,
  	406,3,149,74,0,406,407,3,171,85,0,407,408,3,147,73,0,408,409,3,149,74,
  	0,409,410,3,159,79,0,410,86,1,0,0,0,411,412,5,37,0,0,412,88,1,0,0,0,413,
  	414,5,43,0,0,414,90,1,0,0,0,415,416,5,45,0,0,416,92,1,0,0,0,417,418,5,
  	42,0,0,418,94,1,0,0,0,419,420,5,47,0,0,420,96,1,0,0,0,421,422,5,60,0,
  	0,422,98,1,0,0,0,423,424,5,60,0,0,424,425,5,61,0,0,425,100,1,0,0,0,426,
  	427,5,62,0,0,427,102,1,0,0,0,428,429,5,62,0,0,429,430,5,61,0,0,430,104,
  	1,0,0,0,431,432,5,61,0,0,432,435,5,61,0,0,433,435,5,61,0,0,434,431,1,
  	0,0,0,434,433,1,0,0,0,435,106,1,0,0,0,436,437,5,33,0,0,437,441,5,61,0,
  	0,438,439,5,60,0,0,439,441,5,62,0,0,440,436,1,0,0,0,440,438,1,0,0,0,441,
  	108,1,0,0,0,442,443,5,59,0,0,443,110,1,0,0,0,444,450,5,96,0,0,445,449,
  	8,0,0,0,446,447,5,96,0,0,447,449,5,96,0,0,448,445,1,0,0,0,448,446,1,0,
  	0,0,449,452,1,0,0,0,450,448,1,0,0,0,450,451,1,0,0,0,451,453,1,0,0,0,452,
  	450,1,0,0,0,453,462,5,96,0,0,454,458,7,1,0,0,455,457,7,2,0,0,456,455,
  	1,0,0,0,457,460,1,0,0,0,458,456,1,0,0,0,458,459,1,0,0,0,459,462,1,0,0,
  	0,460,458,1,0,0,0,461,444,1,0,0,0,461,454,1,0,0,0,462,112,1,0,0,0,463,
  	464,3,115,57,0,464,465,5,46,0,0,465,466,3,117,58,0,466,488,1,0,0,0,467,
  	469,3,115,57,0,468,467,1,0,0,0,468,469,1,0,0,0,469,470,1,0,0,0,470,472,
  	5,46,0,0,471,473,3,131,65,0,472,471,1,0,0,0,473,474,1,0,0,0,474,472,1,
  	0,0,0,474,475,1,0,0,0,475,488,1,0,0,0,476,478,3,115,57,0,477,476,1,0,
  	0,0,477,478,1,0,0,0,478,479,1,0,0,0,479,481,5,46,0,0,480,482,3,131,65,
  	0,481,480,1,0,0,0,482,483,1,0,0,0,483,481,1,0,0,0,483,484,1,0,0,0,484,
  	485,1,0,0,0,485,486,3,117,58,0,486,488,1,0,0,0,487,463,1,0,0,0,487,468,
  	1,0,0,0,487,477,1,0,0,0,488,114,1,0,0,0,489,491,3,131,65,0,490,489,1,
  	0,0,0,491,492,1,0,0,0,492,490,1,0,0,0,492,493,1,0,0,0,493,116,1,0,0,0,
  	494,496,3,141,70,0,495,497,5,45,0,0,496,495,1,0,0,0,496,497,1,0,0,0,497,
  	499,1,0,0,0,498,500,3,131,65,0,499,498,1,0,0,0,500,501,1,0,0,0,501,499,
  	1,0,0,0,501,502,1,0,0,0,502,118,1,0,0,0,503,509,5,39,0,0,504,508,8,3,
  	0,0,505,506,5,39,0,0,506,508,5,39,0,0,507,504,1,0,0,0,507,505,1,0,0,0,
  	508,511,1,0,0,0,509,507,1,0,0,0,509,510,1,0,0,0,510,512,1,0,0,0,511,509,
  	1,0,0,0,512,513,5,39,0,0,513,120,1,0,0,0,514,515,3,119,59,0,515,122,1,
  	0,0,0,516,517,5,45,0,0,517,518,5,45,0,0,518,522,1,0,0,0,519,521,8,4,0,
  	0,520,519,1,0,0,0,521,524,1,0,0,0,522,520,1,0,0,0,522,523,1,0,0,0,523,
  	525,1,0,0,0,524,522,1,0,0,0,525,526,6,61,0,0,526,124,1,0,0,0,527,528,
  	5,47,0,0,528,529,5,42,0,0,529,533,1,0,0,0,530,532,9,0,0,0,531,530,1,0,
  	0,0,532,535,1,0,0,0,533,534,1,0,0,0,533,531,1,0,0,0,534,539,1,0,0,0,535,
  	533,1,0,0,0,536,537,5,42,0,0,537,540,5,47,0,0,538,540,5,0,0,1,539,536,
  	1,0,0,0,539,538,1,0,0,0,540,541,1,0,0,0,541,542,6,62,0,0,542,126,1,0,
  	0,0,543,544,7,5,0,0,544,545,1,0,0,0,545,546,6,63,0,0,546,128,1,0,0,0,
  	547,548,9,0,0,0,548,130,1,0,0,0,549,550,7,6,0,0,550,132,1,0,0,0,551,552,
  	7,7,0,0,552,134,1,0,0,0,553,554,7,8,0,0,554,136,1,0,0,0,555,556,7,9,0,
  	0,556,138,1,0,0,0,557,558,7,10,0,0,558,140,1,0,0,0,559,560,7,11,0,0,560,
  	142,1,0,0,0,561,562,7,12,0,0,562,144,1,0,0,0,563,564,7,13,0,0,564,146,
  	1,0,0,0,565,566,7,14,0,0,566,148,1,0,0,0,567,568,7,15,0,0,568,150,1,0,
  	0,0,569,570,7,16,0,0,570,152,1,0,0,0,571,572,7,17,0,0,572,154,1,0,0,0,
  	573,574,7,18,0,0,574,156,1,0,0,0,575,576,7,19,0,0,576,158,1,0,0,0,577,
  	578,7,20,0,0,578,160,1,0,0,0,579,580,7,21,0,0,580,162,1,0,0,0,581,582,
  	7,22,0,0,582,164,1,0,0,0,583,584,7,23,0,0,584,166,1,0,0,0,585,586,7,24,
  	0,0,586,168,1,0,0,0,587,588,7,25,0,0,588,170,1,0,0,0,589,590,7,26,0,0,
  	590,172,1,0,0,0,591,592,7,27,0,0,592,174,1,0,0,0,593,594,7,28,0,0,594,
  	176,1,0,0,0,595,596,7,29,0,0,596,178,1,0,0,0,597,598,7,30,0,0,598,180,
  	1,0,0,0,599,600,7,31,0,0,600,182,1,0,0,0,601,602,7,32,0,0,602,184,1,0,
  	0,0,23,0,306,332,368,434,440,448,450,458,461,468,474,477,483,487,492,
  	496,501,507,509,522,533,539,1,0,1,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  stream_declarationlexerLexerStaticData = staticData.release();
}

}

STREAM_DECLARATIONLexer::STREAM_DECLARATIONLexer(CharStream *input) : Lexer(input) {
  STREAM_DECLARATIONLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *stream_declarationlexerLexerStaticData->atn, stream_declarationlexerLexerStaticData->decisionToDFA, stream_declarationlexerLexerStaticData->sharedContextCache);
}

STREAM_DECLARATIONLexer::~STREAM_DECLARATIONLexer() {
  delete _interpreter;
}

std::string STREAM_DECLARATIONLexer::getGrammarFileName() const {
  return "STREAM_DECLARATION.g4";
}

const std::vector<std::string>& STREAM_DECLARATIONLexer::getRuleNames() const {
  return stream_declarationlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& STREAM_DECLARATIONLexer::getChannelNames() const {
  return stream_declarationlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& STREAM_DECLARATIONLexer::getModeNames() const {
  return stream_declarationlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& STREAM_DECLARATIONLexer::getVocabulary() const {
  return stream_declarationlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView STREAM_DECLARATIONLexer::getSerializedATN() const {
  return stream_declarationlexerLexerStaticData->serializedATN;
}

const atn::ATN& STREAM_DECLARATIONLexer::getATN() const {
  return *stream_declarationlexerLexerStaticData->atn;
}




void STREAM_DECLARATIONLexer::initialize() {
  ::antlr4::internal::call_once(stream_declarationlexerLexerOnceFlag, stream_declarationlexerLexerInitialize);
}
