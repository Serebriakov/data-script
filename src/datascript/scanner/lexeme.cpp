#include <iostream>

#include "datascript/scanner/lexeme.hpp"
DATASCRIPT_SCANNER_NS_BEGIN
const char* token_to_string (token_t token)
{
  switch (token)
    {
    case eWHITESPACE:
      return "WS";
    case eDECIMAL_NUMBER:
      return "DECIMAL NUMBER";
    case eHEX_NUMBER:
      return "HEX NUMBER";
    case eBINARY_NUMBER:
      return "BINARY NUMBER";
    case eOCTAL_NUMBER:
      return "OCTAL NUMBER";
    case eSTRING:
      return "STRING";
    case eINT8:
      return "INT8";
    case eINT16:
      return "INT16";
    case eINT32:
      return "INT32";  
    case eINT64:
      return "INT64";
    case eUINT8:
      return "UINT8";
    case eUINT16:
      return "UINT16";
    case eUINT32:
      return "UINT32";  
    case eUINT64:
      return "UINT64";  
    case eBIT:  
      return "BIT";
    case eCOLON:
      return "COLON";
    case eSEMICOLON:
      return "SEMICOL";
    case eEQ:
      return "EQ";
    case eEQEQ:
      return "EQEQ";
    case eID:
      return "ID";
    case eLEFT_CURL_BRACKET:
      return "LEFT CURL BRACK";
    case eRIGHT_CURL_BRACKET:
      return "RIGHT CURL BRACK";
    case eLEFT_BRACKET:
      return "LEFT BRACK";
    case eRIGHT_BRACKET:
      return "RIGHT BRACK";
    case eLEFT_PAREN:
      return "LEFT PAREN";
    case eRIGHT_PAREN:
      return "RIGHT PAREN";
    case eUNION:
      return "UNION";
    case eCHOICE:
      return "CHOICE";
    case eON:
      return "ON";
    case eCASE:
      return "CASE";
    case eIF:
      return "IF";
    case eFUNCTION:
      return "FUNC";
    case eALIGN:
      return "ALIGN";
    case eLT:
      return "LT";
    case eLEQ:
      return "LEQ";
    case eGT:
      return "GT";
    case eGEQ:
      return "GEQ";
    case eNEQ:
      return "NEQ";
    case eLOGIC_AND:
      return "LOG-AND";
    case eLOGIC_OR:
      return "LOG-OR";
    case eLOGIC_NOT:
      return "LOG-NOT";  
    case eAND:
      return "AND";
    case eOR:
      return "OR";
    case eXOR:
      return "XOR";
    case eASS_MUL:
      return "ASSIGN MUL";
    case eASS_DIV:
      return "ASSIGN DIV";
    case eASS_MOD:
      return "ASSIGN MOD";
    case eASS_PLUS:
      return "ASSIGN PLUS";
    case eASS_MINUS:
      return "ASSIGN MINUS";
    case eASS_SHR:
      return "ASSIGN SHR";
    case eASS_SHL:
      return "ASSIGN SHL";
    case eASS_AND:
      return "ASSIGN AND";
    case eASS_OR:
      return "ASSIGN OR";
    case eASS_XOR:
      return "ASSIGN XOR";
    case ePLUS:
      return "PLUS";
    case eMINUS:
      return "MINUS";
    case eNOT:
      return "NOT";
    case eDIV:
      return "DIV";
    case eMUL:
      return "MUL";
    case eMOD:
      return "MOD";
    case eSHR:
      return "SHR";
    case eSHL:
      return "SHL";
    case eSIZEOF:
      return "SIZEOF";
    case eBITSIZEOF:
      return "BITSIZEOF";
    case eLENGTHOF:
      return "LENGTHOF";
    case eIS:
      return "IS";
    case eSUM:
      return "SUM";
    case eQUESTION:
      return "QUESTION";
    case eFORALL:
      return "FORALL";
    case ePACKAGE:
      return "PACKAGE";
    case eIMPORT:
      return "IMPORT";
    case eEND_OF_FILE:
      return "END-OF-FILE";
    case eUNTERMINATED_STRING:
      return "ERROR: unterminated string";
    case eUNKNOWN_LEXEME:
      return "ERROR: unknown lexeme";
    };
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code"
#endif

  return "UNKNOWN";
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}

std::ostream& operator << (std::ostream& os, token_t token)
{
  os << token_to_string (token);
  return os;
}



DATASCRIPT_SCANNER_NS_END