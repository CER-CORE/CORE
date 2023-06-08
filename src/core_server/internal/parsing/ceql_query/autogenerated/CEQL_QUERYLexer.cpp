
// Generated from CEQL_QUERY.g4 by ANTLR 4.12.0


#include "CEQL_QUERYLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CEQL_QUERYLexerStaticData final {
  CEQL_QUERYLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CEQL_QUERYLexerStaticData(const CEQL_QUERYLexerStaticData&) = delete;
  CEQL_QUERYLexerStaticData(CEQL_QUERYLexerStaticData&&) = delete;
  CEQL_QUERYLexerStaticData& operator=(const CEQL_QUERYLexerStaticData&) = delete;
  CEQL_QUERYLexerStaticData& operator=(CEQL_QUERYLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag ceql_querylexerLexerOnceFlag;
CEQL_QUERYLexerStaticData *ceql_querylexerLexerStaticData = nullptr;

void ceql_querylexerLexerInitialize() {
  assert(ceql_querylexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<CEQL_QUERYLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "K_ALL", 
      "K_AND", "K_ANY", "K_AS", "K_BY", "K_CONSUME", "K_DISTINCT", "K_EVENT", 
      "K_EVENTS", "K_FILTER", "K_FROM", "K_HOURS", "K_IN", "K_LAST", "K_LIKE", 
      "K_MAX", "K_MINUTES", "K_NEXT", "K_NONE", "K_NOT", "K_OR", "K_PARTITION", 
      "K_SECONDS", "K_SELECT", "K_STREAM", "K_STRICT", "K_UNLESS", "K_WHERE", 
      "K_WITHIN", "PERCENT", "PLUS", "MINUS", "STAR", "SLASH", "LE", "LEQ", 
      "GE", "GEQ", "EQ", "NEQ", "SEMICOLON", "IDENTIFIER", "DOUBLE_LITERAL", 
      "INTEGER_LITERAL", "NUMERICAL_EXPONENT", "STRING_LITERAL", "SINGLE_LINE_COMMENT", 
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
      "", "','", "'('", "')'", "'['", "']'", "'{'", "'}'", "'..'", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "'%'", "'+'", "'-'", "'*'", 
      "'/'", "'<'", "'<='", "'>'", "'>='", "", "", "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "K_ALL", "K_AND", "K_ANY", "K_AS", 
      "K_BY", "K_CONSUME", "K_DISTINCT", "K_EVENT", "K_EVENTS", "K_FILTER", 
      "K_FROM", "K_HOURS", "K_IN", "K_LAST", "K_LIKE", "K_MAX", "K_MINUTES", 
      "K_NEXT", "K_NONE", "K_NOT", "K_OR", "K_PARTITION", "K_SECONDS", "K_SELECT", 
      "K_STREAM", "K_STRICT", "K_UNLESS", "K_WHERE", "K_WITHIN", "PERCENT", 
      "PLUS", "MINUS", "STAR", "SLASH", "LE", "LEQ", "GE", "GEQ", "EQ", 
      "NEQ", "SEMICOLON", "IDENTIFIER", "DOUBLE_LITERAL", "INTEGER_LITERAL", 
      "NUMERICAL_EXPONENT", "STRING_LITERAL", "SINGLE_LINE_COMMENT", "MULTILINE_COMMENT", 
      "SPACES", "UNEXPECTED_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,58,548,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
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
  	7,84,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,
  	1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,
  	1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,
  	1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,3,19,254,8,19,1,20,1,20,1,20,
  	1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,
  	1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,280,8,24,1,25,1,25,1,25,1,25,
  	1,25,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,3,30,316,8,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,37,1,37,1,38,1,38,1,39,1,39,1,40,1,40,1,41,1,41,
  	1,42,1,42,1,43,1,43,1,43,1,44,1,44,1,45,1,45,1,45,1,46,1,46,1,46,3,46,
  	382,8,46,1,47,1,47,1,47,1,47,3,47,388,8,47,1,48,1,48,1,49,1,49,1,49,1,
  	49,5,49,396,8,49,10,49,12,49,399,9,49,1,49,1,49,1,49,5,49,404,8,49,10,
  	49,12,49,407,9,49,3,49,409,8,49,1,50,1,50,1,50,1,50,1,50,3,50,416,8,50,
  	1,50,1,50,4,50,420,8,50,11,50,12,50,421,1,50,3,50,425,8,50,1,50,1,50,
  	4,50,429,8,50,11,50,12,50,430,1,50,1,50,3,50,435,8,50,1,51,4,51,438,8,
  	51,11,51,12,51,439,1,52,1,52,3,52,444,8,52,1,52,4,52,447,8,52,11,52,12,
  	52,448,1,53,1,53,1,53,1,53,5,53,455,8,53,10,53,12,53,458,9,53,1,53,1,
  	53,1,54,1,54,1,54,1,54,5,54,466,8,54,10,54,12,54,469,9,54,1,54,1,54,1,
  	55,1,55,1,55,1,55,5,55,477,8,55,10,55,12,55,480,9,55,1,55,1,55,1,55,3,
  	55,485,8,55,1,55,1,55,1,56,1,56,1,56,1,56,1,57,1,57,1,58,1,58,1,59,1,
  	59,1,60,1,60,1,61,1,61,1,62,1,62,1,63,1,63,1,64,1,64,1,65,1,65,1,66,1,
  	66,1,67,1,67,1,68,1,68,1,69,1,69,1,70,1,70,1,71,1,71,1,72,1,72,1,73,1,
  	73,1,74,1,74,1,75,1,75,1,76,1,76,1,77,1,77,1,78,1,78,1,79,1,79,1,80,1,
  	80,1,81,1,81,1,82,1,82,1,83,1,83,1,84,1,84,1,478,0,85,1,1,3,2,5,3,7,4,
  	9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,
  	17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,
  	57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,
  	40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,49,99,50,101,51,
  	103,52,105,53,107,54,109,55,111,56,113,57,115,58,117,0,119,0,121,0,123,
  	0,125,0,127,0,129,0,131,0,133,0,135,0,137,0,139,0,141,0,143,0,145,0,147,
  	0,149,0,151,0,153,0,155,0,157,0,159,0,161,0,163,0,165,0,167,0,169,0,1,
  	0,33,1,0,96,96,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,1,
  	0,39,39,2,0,10,10,13,13,3,0,9,11,13,13,32,32,1,0,48,57,2,0,65,65,97,97,
  	2,0,66,66,98,98,2,0,67,67,99,99,2,0,68,68,100,100,2,0,69,69,101,101,2,
  	0,70,70,102,102,2,0,71,71,103,103,2,0,72,72,104,104,2,0,73,73,105,105,
  	2,0,74,74,106,106,2,0,75,75,107,107,2,0,76,76,108,108,2,0,77,77,109,109,
  	2,0,78,78,110,110,2,0,79,79,111,111,2,0,80,80,112,112,2,0,81,81,113,113,
  	2,0,82,82,114,114,2,0,83,83,115,115,2,0,84,84,116,116,2,0,85,85,117,117,
  	2,0,86,86,118,118,2,0,87,87,119,119,2,0,88,88,120,120,2,0,89,89,121,121,
  	2,0,90,90,122,122,543,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,
  	0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,
  	1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,
  	0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,
  	0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,
  	1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,
  	0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,
  	0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,
  	1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,
  	0,0,0,95,1,0,0,0,0,97,1,0,0,0,0,99,1,0,0,0,0,101,1,0,0,0,0,103,1,0,0,
  	0,0,105,1,0,0,0,0,107,1,0,0,0,0,109,1,0,0,0,0,111,1,0,0,0,0,113,1,0,0,
  	0,0,115,1,0,0,0,1,171,1,0,0,0,3,173,1,0,0,0,5,175,1,0,0,0,7,177,1,0,0,
  	0,9,179,1,0,0,0,11,181,1,0,0,0,13,183,1,0,0,0,15,185,1,0,0,0,17,188,1,
  	0,0,0,19,192,1,0,0,0,21,196,1,0,0,0,23,200,1,0,0,0,25,203,1,0,0,0,27,
  	206,1,0,0,0,29,214,1,0,0,0,31,223,1,0,0,0,33,229,1,0,0,0,35,236,1,0,0,
  	0,37,243,1,0,0,0,39,248,1,0,0,0,41,255,1,0,0,0,43,258,1,0,0,0,45,263,
  	1,0,0,0,47,268,1,0,0,0,49,272,1,0,0,0,51,281,1,0,0,0,53,286,1,0,0,0,55,
  	291,1,0,0,0,57,295,1,0,0,0,59,298,1,0,0,0,61,308,1,0,0,0,63,317,1,0,0,
  	0,65,324,1,0,0,0,67,331,1,0,0,0,69,338,1,0,0,0,71,345,1,0,0,0,73,351,
  	1,0,0,0,75,358,1,0,0,0,77,360,1,0,0,0,79,362,1,0,0,0,81,364,1,0,0,0,83,
  	366,1,0,0,0,85,368,1,0,0,0,87,370,1,0,0,0,89,373,1,0,0,0,91,375,1,0,0,
  	0,93,381,1,0,0,0,95,387,1,0,0,0,97,389,1,0,0,0,99,408,1,0,0,0,101,434,
  	1,0,0,0,103,437,1,0,0,0,105,441,1,0,0,0,107,450,1,0,0,0,109,461,1,0,0,
  	0,111,472,1,0,0,0,113,488,1,0,0,0,115,492,1,0,0,0,117,494,1,0,0,0,119,
  	496,1,0,0,0,121,498,1,0,0,0,123,500,1,0,0,0,125,502,1,0,0,0,127,504,1,
  	0,0,0,129,506,1,0,0,0,131,508,1,0,0,0,133,510,1,0,0,0,135,512,1,0,0,0,
  	137,514,1,0,0,0,139,516,1,0,0,0,141,518,1,0,0,0,143,520,1,0,0,0,145,522,
  	1,0,0,0,147,524,1,0,0,0,149,526,1,0,0,0,151,528,1,0,0,0,153,530,1,0,0,
  	0,155,532,1,0,0,0,157,534,1,0,0,0,159,536,1,0,0,0,161,538,1,0,0,0,163,
  	540,1,0,0,0,165,542,1,0,0,0,167,544,1,0,0,0,169,546,1,0,0,0,171,172,5,
  	44,0,0,172,2,1,0,0,0,173,174,5,40,0,0,174,4,1,0,0,0,175,176,5,41,0,0,
  	176,6,1,0,0,0,177,178,5,91,0,0,178,8,1,0,0,0,179,180,5,93,0,0,180,10,
  	1,0,0,0,181,182,5,123,0,0,182,12,1,0,0,0,183,184,5,125,0,0,184,14,1,0,
  	0,0,185,186,5,46,0,0,186,187,5,46,0,0,187,16,1,0,0,0,188,189,3,119,59,
  	0,189,190,3,141,70,0,190,191,3,141,70,0,191,18,1,0,0,0,192,193,3,119,
  	59,0,193,194,3,145,72,0,194,195,3,125,62,0,195,20,1,0,0,0,196,197,3,119,
  	59,0,197,198,3,145,72,0,198,199,3,167,83,0,199,22,1,0,0,0,200,201,3,119,
  	59,0,201,202,3,155,77,0,202,24,1,0,0,0,203,204,3,121,60,0,204,205,3,167,
  	83,0,205,26,1,0,0,0,206,207,3,123,61,0,207,208,3,147,73,0,208,209,3,145,
  	72,0,209,210,3,155,77,0,210,211,3,159,79,0,211,212,3,143,71,0,212,213,
  	3,127,63,0,213,28,1,0,0,0,214,215,3,125,62,0,215,216,3,135,67,0,216,217,
  	3,155,77,0,217,218,3,157,78,0,218,219,3,135,67,0,219,220,3,145,72,0,220,
  	221,3,123,61,0,221,222,3,157,78,0,222,30,1,0,0,0,223,224,3,127,63,0,224,
  	225,3,161,80,0,225,226,3,127,63,0,226,227,3,145,72,0,227,228,3,157,78,
  	0,228,32,1,0,0,0,229,230,3,127,63,0,230,231,3,161,80,0,231,232,3,127,
  	63,0,232,233,3,145,72,0,233,234,3,157,78,0,234,235,3,155,77,0,235,34,
  	1,0,0,0,236,237,3,129,64,0,237,238,3,135,67,0,238,239,3,141,70,0,239,
  	240,3,157,78,0,240,241,3,127,63,0,241,242,3,153,76,0,242,36,1,0,0,0,243,
  	244,3,129,64,0,244,245,3,153,76,0,245,246,3,147,73,0,246,247,3,143,71,
  	0,247,38,1,0,0,0,248,249,3,133,66,0,249,250,3,147,73,0,250,251,3,159,
  	79,0,251,253,3,153,76,0,252,254,3,155,77,0,253,252,1,0,0,0,253,254,1,
  	0,0,0,254,40,1,0,0,0,255,256,3,135,67,0,256,257,3,145,72,0,257,42,1,0,
  	0,0,258,259,3,141,70,0,259,260,3,119,59,0,260,261,3,155,77,0,261,262,
  	3,157,78,0,262,44,1,0,0,0,263,264,3,141,70,0,264,265,3,135,67,0,265,266,
  	3,139,69,0,266,267,3,127,63,0,267,46,1,0,0,0,268,269,3,143,71,0,269,270,
  	3,119,59,0,270,271,3,165,82,0,271,48,1,0,0,0,272,273,3,143,71,0,273,274,
  	3,135,67,0,274,275,3,145,72,0,275,276,3,159,79,0,276,277,3,157,78,0,277,
  	279,3,127,63,0,278,280,3,155,77,0,279,278,1,0,0,0,279,280,1,0,0,0,280,
  	50,1,0,0,0,281,282,3,145,72,0,282,283,3,127,63,0,283,284,3,165,82,0,284,
  	285,3,157,78,0,285,52,1,0,0,0,286,287,3,145,72,0,287,288,3,147,73,0,288,
  	289,3,145,72,0,289,290,3,127,63,0,290,54,1,0,0,0,291,292,3,145,72,0,292,
  	293,3,147,73,0,293,294,3,157,78,0,294,56,1,0,0,0,295,296,3,147,73,0,296,
  	297,3,153,76,0,297,58,1,0,0,0,298,299,3,149,74,0,299,300,3,119,59,0,300,
  	301,3,153,76,0,301,302,3,157,78,0,302,303,3,135,67,0,303,304,3,157,78,
  	0,304,305,3,135,67,0,305,306,3,147,73,0,306,307,3,145,72,0,307,60,1,0,
  	0,0,308,309,3,155,77,0,309,310,3,127,63,0,310,311,3,123,61,0,311,312,
  	3,147,73,0,312,313,3,145,72,0,313,315,3,125,62,0,314,316,3,155,77,0,315,
  	314,1,0,0,0,315,316,1,0,0,0,316,62,1,0,0,0,317,318,3,155,77,0,318,319,
  	3,127,63,0,319,320,3,141,70,0,320,321,3,127,63,0,321,322,3,123,61,0,322,
  	323,3,157,78,0,323,64,1,0,0,0,324,325,3,155,77,0,325,326,3,157,78,0,326,
  	327,3,153,76,0,327,328,3,127,63,0,328,329,3,119,59,0,329,330,3,143,71,
  	0,330,66,1,0,0,0,331,332,3,155,77,0,332,333,3,157,78,0,333,334,3,153,
  	76,0,334,335,3,135,67,0,335,336,3,123,61,0,336,337,3,157,78,0,337,68,
  	1,0,0,0,338,339,3,159,79,0,339,340,3,145,72,0,340,341,3,141,70,0,341,
  	342,3,127,63,0,342,343,3,155,77,0,343,344,3,155,77,0,344,70,1,0,0,0,345,
  	346,3,163,81,0,346,347,3,133,66,0,347,348,3,127,63,0,348,349,3,153,76,
  	0,349,350,3,127,63,0,350,72,1,0,0,0,351,352,3,163,81,0,352,353,3,135,
  	67,0,353,354,3,157,78,0,354,355,3,133,66,0,355,356,3,135,67,0,356,357,
  	3,145,72,0,357,74,1,0,0,0,358,359,5,37,0,0,359,76,1,0,0,0,360,361,5,43,
  	0,0,361,78,1,0,0,0,362,363,5,45,0,0,363,80,1,0,0,0,364,365,5,42,0,0,365,
  	82,1,0,0,0,366,367,5,47,0,0,367,84,1,0,0,0,368,369,5,60,0,0,369,86,1,
  	0,0,0,370,371,5,60,0,0,371,372,5,61,0,0,372,88,1,0,0,0,373,374,5,62,0,
  	0,374,90,1,0,0,0,375,376,5,62,0,0,376,377,5,61,0,0,377,92,1,0,0,0,378,
  	379,5,61,0,0,379,382,5,61,0,0,380,382,5,61,0,0,381,378,1,0,0,0,381,380,
  	1,0,0,0,382,94,1,0,0,0,383,384,5,33,0,0,384,388,5,61,0,0,385,386,5,60,
  	0,0,386,388,5,62,0,0,387,383,1,0,0,0,387,385,1,0,0,0,388,96,1,0,0,0,389,
  	390,5,59,0,0,390,98,1,0,0,0,391,397,5,96,0,0,392,396,8,0,0,0,393,394,
  	5,96,0,0,394,396,5,96,0,0,395,392,1,0,0,0,395,393,1,0,0,0,396,399,1,0,
  	0,0,397,395,1,0,0,0,397,398,1,0,0,0,398,400,1,0,0,0,399,397,1,0,0,0,400,
  	409,5,96,0,0,401,405,7,1,0,0,402,404,7,2,0,0,403,402,1,0,0,0,404,407,
  	1,0,0,0,405,403,1,0,0,0,405,406,1,0,0,0,406,409,1,0,0,0,407,405,1,0,0,
  	0,408,391,1,0,0,0,408,401,1,0,0,0,409,100,1,0,0,0,410,411,3,103,51,0,
  	411,412,5,46,0,0,412,413,3,105,52,0,413,435,1,0,0,0,414,416,3,103,51,
  	0,415,414,1,0,0,0,415,416,1,0,0,0,416,417,1,0,0,0,417,419,5,46,0,0,418,
  	420,3,117,58,0,419,418,1,0,0,0,420,421,1,0,0,0,421,419,1,0,0,0,421,422,
  	1,0,0,0,422,435,1,0,0,0,423,425,3,103,51,0,424,423,1,0,0,0,424,425,1,
  	0,0,0,425,426,1,0,0,0,426,428,5,46,0,0,427,429,3,117,58,0,428,427,1,0,
  	0,0,429,430,1,0,0,0,430,428,1,0,0,0,430,431,1,0,0,0,431,432,1,0,0,0,432,
  	433,3,105,52,0,433,435,1,0,0,0,434,410,1,0,0,0,434,415,1,0,0,0,434,424,
  	1,0,0,0,435,102,1,0,0,0,436,438,3,117,58,0,437,436,1,0,0,0,438,439,1,
  	0,0,0,439,437,1,0,0,0,439,440,1,0,0,0,440,104,1,0,0,0,441,443,3,127,63,
  	0,442,444,5,45,0,0,443,442,1,0,0,0,443,444,1,0,0,0,444,446,1,0,0,0,445,
  	447,3,117,58,0,446,445,1,0,0,0,447,448,1,0,0,0,448,446,1,0,0,0,448,449,
  	1,0,0,0,449,106,1,0,0,0,450,456,5,39,0,0,451,455,8,3,0,0,452,453,5,39,
  	0,0,453,455,5,39,0,0,454,451,1,0,0,0,454,452,1,0,0,0,455,458,1,0,0,0,
  	456,454,1,0,0,0,456,457,1,0,0,0,457,459,1,0,0,0,458,456,1,0,0,0,459,460,
  	5,39,0,0,460,108,1,0,0,0,461,462,5,45,0,0,462,463,5,45,0,0,463,467,1,
  	0,0,0,464,466,8,4,0,0,465,464,1,0,0,0,466,469,1,0,0,0,467,465,1,0,0,0,
  	467,468,1,0,0,0,468,470,1,0,0,0,469,467,1,0,0,0,470,471,6,54,0,0,471,
  	110,1,0,0,0,472,473,5,47,0,0,473,474,5,42,0,0,474,478,1,0,0,0,475,477,
  	9,0,0,0,476,475,1,0,0,0,477,480,1,0,0,0,478,479,1,0,0,0,478,476,1,0,0,
  	0,479,484,1,0,0,0,480,478,1,0,0,0,481,482,5,42,0,0,482,485,5,47,0,0,483,
  	485,5,0,0,1,484,481,1,0,0,0,484,483,1,0,0,0,485,486,1,0,0,0,486,487,6,
  	55,0,0,487,112,1,0,0,0,488,489,7,5,0,0,489,490,1,0,0,0,490,491,6,56,0,
  	0,491,114,1,0,0,0,492,493,9,0,0,0,493,116,1,0,0,0,494,495,7,6,0,0,495,
  	118,1,0,0,0,496,497,7,7,0,0,497,120,1,0,0,0,498,499,7,8,0,0,499,122,1,
  	0,0,0,500,501,7,9,0,0,501,124,1,0,0,0,502,503,7,10,0,0,503,126,1,0,0,
  	0,504,505,7,11,0,0,505,128,1,0,0,0,506,507,7,12,0,0,507,130,1,0,0,0,508,
  	509,7,13,0,0,509,132,1,0,0,0,510,511,7,14,0,0,511,134,1,0,0,0,512,513,
  	7,15,0,0,513,136,1,0,0,0,514,515,7,16,0,0,515,138,1,0,0,0,516,517,7,17,
  	0,0,517,140,1,0,0,0,518,519,7,18,0,0,519,142,1,0,0,0,520,521,7,19,0,0,
  	521,144,1,0,0,0,522,523,7,20,0,0,523,146,1,0,0,0,524,525,7,21,0,0,525,
  	148,1,0,0,0,526,527,7,22,0,0,527,150,1,0,0,0,528,529,7,23,0,0,529,152,
  	1,0,0,0,530,531,7,24,0,0,531,154,1,0,0,0,532,533,7,25,0,0,533,156,1,0,
  	0,0,534,535,7,26,0,0,535,158,1,0,0,0,536,537,7,27,0,0,537,160,1,0,0,0,
  	538,539,7,28,0,0,539,162,1,0,0,0,540,541,7,29,0,0,541,164,1,0,0,0,542,
  	543,7,30,0,0,543,166,1,0,0,0,544,545,7,31,0,0,545,168,1,0,0,0,546,547,
  	7,32,0,0,547,170,1,0,0,0,23,0,253,279,315,381,387,395,397,405,408,415,
  	421,424,430,434,439,443,448,454,456,467,478,484,1,0,1,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ceql_querylexerLexerStaticData = staticData.release();
}

}

CEQL_QUERYLexer::CEQL_QUERYLexer(CharStream *input) : Lexer(input) {
  CEQL_QUERYLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ceql_querylexerLexerStaticData->atn, ceql_querylexerLexerStaticData->decisionToDFA, ceql_querylexerLexerStaticData->sharedContextCache);
}

CEQL_QUERYLexer::~CEQL_QUERYLexer() {
  delete _interpreter;
}

std::string CEQL_QUERYLexer::getGrammarFileName() const {
  return "CEQL_QUERY.g4";
}

const std::vector<std::string>& CEQL_QUERYLexer::getRuleNames() const {
  return ceql_querylexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CEQL_QUERYLexer::getChannelNames() const {
  return ceql_querylexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CEQL_QUERYLexer::getModeNames() const {
  return ceql_querylexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CEQL_QUERYLexer::getVocabulary() const {
  return ceql_querylexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CEQL_QUERYLexer::getSerializedATN() const {
  return ceql_querylexerLexerStaticData->serializedATN;
}

const atn::ATN& CEQL_QUERYLexer::getATN() const {
  return *ceql_querylexerLexerStaticData->atn;
}




void CEQL_QUERYLexer::initialize() {
  ::antlr4::internal::call_once(ceql_querylexerLexerOnceFlag, ceql_querylexerLexerInitialize);
}