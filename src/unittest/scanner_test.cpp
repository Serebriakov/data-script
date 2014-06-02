#include "unittest/catch.hpp"

#include "datascript/scanner/lexer.hpp"
#include "datascript/scanner/io.hpp"

#define STRINGIZE_DIRECT(E) #E
#define STRINGIZE(E) STRINGIZE_DIRECT(E)

#define SIMPLE_LEXER_TEST(EXPECTED, EXPR)				\
  TEST_CASE ("SIMPLE_LEXER_TEST_" STRINGIZE(EXPECTED) "_" STRINGIZE (__LINE__), "") \
  {									\
    input_buffer_t* input = DATASCRIPT_SCANNER_NS open_string (EXPR);	\
    DATASCRIPT_SCANNER_NS lexer ds_scanner (input);			\
    int k = 0;								\
    while (true)							\
      {									\
	token_t tok = ds_scanner.scan ();				\
	if (k == 0)							\
	  {								\
	    REQUIRE (tok == EXPECTED);					\
	    k++;							\
	  }								\
	else								\
	  {								\
	    REQUIRE (tok == eEND_OF_FILE);				\
	  }								\
	if (tok >= eEND_OF_FILE)					\
	  {								\
	    break;							\
	  }								\
      }									\
    close_buffer (input);						\
  }  

#define SIMPLE_LEXER_TEST_ERR(EXPR)					\
  TEST_CASE ("SIMPLE_LEXER_TEST_ERR_" STRINGIZE (__LINE__), "")		\
  {									\
    input_buffer_t* input = DATASCRIPT_SCANNER_NS open_string (EXPR);	\
    DATASCRIPT_SCANNER_NS lexer ds_scanner (input);			\
    token_t tok = ds_scanner.scan ();					\
    REQUIRE (tok == eUNKNOWN_LEXEME);					\
    close_buffer (input);						\
  }  

// ================================================================================
SIMPLE_LEXER_TEST (eWHITESPACE    , " ")
SIMPLE_LEXER_TEST (eDECIMAL_NUMBER, "123")
SIMPLE_LEXER_TEST (eHEX_NUMBER    , "0x12")
SIMPLE_LEXER_TEST (eOCTAL_NUMBER  , "03")
SIMPLE_LEXER_TEST (eBINARY_NUMBER , "10101b")

SIMPLE_LEXER_TEST (eSTRING        , "\"string\"")
SIMPLE_LEXER_TEST (eSTRING        , "\"\"")


SIMPLE_LEXER_TEST (eUINT8         , "uint8")
SIMPLE_LEXER_TEST (eUINT16        , "uint16")
SIMPLE_LEXER_TEST (eUINT32        , "uint32")
SIMPLE_LEXER_TEST (eUINT64        , "uint64")
SIMPLE_LEXER_TEST (eINT8          , "int8")
SIMPLE_LEXER_TEST (eINT16         , "int16")
SIMPLE_LEXER_TEST (eINT32         , "int32")
SIMPLE_LEXER_TEST (eINT64         , "int64")

SIMPLE_LEXER_TEST (eBIT           , "bit")

SIMPLE_LEXER_TEST (eCOLON         , ":")
SIMPLE_LEXER_TEST (eSEMICOLON     , ";")
SIMPLE_LEXER_TEST (eEQ            , "=")
SIMPLE_LEXER_TEST (eEQEQ          , "==")

SIMPLE_LEXER_TEST (eID            , "_zopa_123")
SIMPLE_LEXER_TEST (eID            , "_")


SIMPLE_LEXER_TEST (eLT, "<")
SIMPLE_LEXER_TEST (eLEQ, "<=")
SIMPLE_LEXER_TEST (eGT, ">")
SIMPLE_LEXER_TEST (eGEQ, ">=")
SIMPLE_LEXER_TEST (eNEQ, "!=")
SIMPLE_LEXER_TEST (eLOGIC_AND, "&&")
SIMPLE_LEXER_TEST (eLOGIC_OR, "||")
SIMPLE_LEXER_TEST (eLOGIC_NOT, "!")
SIMPLE_LEXER_TEST (eASS_MUL, "*=")
SIMPLE_LEXER_TEST (eASS_DIV, "/=")
SIMPLE_LEXER_TEST (eASS_MOD, "%=")
SIMPLE_LEXER_TEST (eASS_PLUS, "+=")
SIMPLE_LEXER_TEST (eASS_MINUS, "-=")
SIMPLE_LEXER_TEST (eASS_SHR, ">>=")
SIMPLE_LEXER_TEST (eASS_SHL, "<<=")
SIMPLE_LEXER_TEST (eASS_AND, "&=")
SIMPLE_LEXER_TEST (eASS_OR, "|=")
SIMPLE_LEXER_TEST (eASS_XOR, "^=")
SIMPLE_LEXER_TEST (eAND, "&")
SIMPLE_LEXER_TEST (eOR, "|")
SIMPLE_LEXER_TEST (eXOR, "^")
SIMPLE_LEXER_TEST (ePLUS, "+")
SIMPLE_LEXER_TEST (eMINUS, "-")
SIMPLE_LEXER_TEST (eNOT, "~")
SIMPLE_LEXER_TEST (eDIV, "/")
SIMPLE_LEXER_TEST (eMUL, "*")
SIMPLE_LEXER_TEST (eMOD, "%")
SIMPLE_LEXER_TEST (eSHR, ">>")
SIMPLE_LEXER_TEST (eSHL, "<<")

SIMPLE_LEXER_TEST (eLEFT_CURL_BRACKET, "{")
SIMPLE_LEXER_TEST (eRIGHT_CURL_BRACKET, "}")
SIMPLE_LEXER_TEST (eLEFT_BRACKET, "[")
SIMPLE_LEXER_TEST (eRIGHT_BRACKET, "]")
SIMPLE_LEXER_TEST (eLEFT_PAREN, "(")
SIMPLE_LEXER_TEST (eRIGHT_PAREN, ")")
SIMPLE_LEXER_TEST (eUNION, "union")
SIMPLE_LEXER_TEST (eCHOICE, "choice")
SIMPLE_LEXER_TEST (eON, "on")
SIMPLE_LEXER_TEST (eCASE, "case")
SIMPLE_LEXER_TEST (eIF, "if")
SIMPLE_LEXER_TEST (eFUNCTION, "function")
SIMPLE_LEXER_TEST (eALIGN, "align")
SIMPLE_LEXER_TEST (eSIZEOF, "sizeof")
SIMPLE_LEXER_TEST (eBITSIZEOF, "bitsizeof")
SIMPLE_LEXER_TEST (eLENGTHOF, "lengthof")
SIMPLE_LEXER_TEST (eIS, "is")
SIMPLE_LEXER_TEST (eSUM, "sum")
SIMPLE_LEXER_TEST (eQUESTION, "?")
SIMPLE_LEXER_TEST (eFORALL, "forall")
SIMPLE_LEXER_TEST (ePACKAGE, "package")
SIMPLE_LEXER_TEST (eIMPORT, "import")



SIMPLE_LEXER_TEST_ERR ("$")

