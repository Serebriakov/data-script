#ifndef __DATASCRIPT_PARSER_TOKENS_H__
#define __DATASCRIPT_PARSER_TOKENS_H__

#if defined(__cplusplus)
#include <iosfwd>
#endif

typedef enum token_tag 
{
  eDECIMAL_NUMBER,
  eHEX_NUMBER,
  eBINARY_NUMBER,
  eOCTAL_NUMBER,
  eSTRING,
  eUINT8,
  eUINT16,
  eUINT32,
  eUINT64,
  eINT8,
  eINT16,
  eINT32,
  eINT64,
  eBIT,
  eCOLON,
  eSEMICOLON,
  eEQ,
  eLT,
  eLEQ,
  eGT,
  eGEQ,
  eNEQ,
  eEQEQ,
  eLOGIC_AND,
  eLOGIC_OR,
  eLOGIC_NOT,
  eASS_MUL,
  eASS_DIV,
  eASS_MOD,
  eASS_PLUS,
  eASS_MINUS,
  eASS_SHR,
  eASS_SHL,
  eASS_AND,
  eASS_OR,
  eASS_XOR,
  eAND,
  eOR,
  eXOR,
  

  ePLUS,
  eMINUS,
  eNOT,
  eDIV,
  eMUL,
  eMOD,
  eSHR,
  eSHL,

  eID,
  eLEFT_CURL_BRACKET,
  eRIGHT_CURL_BRACKET,
  eLEFT_BRACKET,
  eRIGHT_BRACKET,
  eLEFT_PAREN,
  eRIGHT_PAREN,
  eUNION,
  eCHOICE,
  eON,
  eCASE,
  eIF,
  eFUNCTION,
  eALIGN,
  
  eSIZEOF,
  eBITSIZEOF,
  eLENGTHOF,
  eIS,
  eSUM,
  eQUESTION,
  eFORALL,
  
  ePACKAGE,
  eIMPORT,

  eEND_OF_FILE,

  eUNTERMINATED_STRING,
  eUNKNOWN_LEXEME
} token_t;

#if defined(__cplusplus)
extern "C"
#endif
const char* token_to_string (token_t token);


#if defined(__cplusplus)
std::ostream& operator << (std::ostream& os, token_t token);
#endif


#endif

