#ifndef __DATASCRIPT_SCANNER_LEXEME_HPP__
#define __DATASCRIPT_SCANNER_LEXEME_HPP__

#include <iosfwd>

#include "datascript/scanner/tokens.h"
#include "datascript/datascript_api.h"

namespace datascript
{
	namespace scanner
	{
		enum token_t
		{
			eWHITESPACE = WHITESPACE,
			eDECIMAL_NUMBER = DECIMAL_NUMBER,
			eHEX_NUMBER = HEX_NUMBER,
			eBINARY_NUMBER = BINARY_NUMBER,
			eOCTAL_NUMBER = OCTAL_NUMBER,
			eSTRING = STRING,
			eUINT8 = UINT8,
			eUINT16 = UINT16,
			eUINT32 = UINT32,
			eUINT64 = UINT64,
			eINT8 = INT8,
			eINT16 = INT16,
			eINT32 = INT32,
			eINT64 = INT64,
			eBIT = BIT,
			eCOLON = COLON,
			eSEMICOLON = SEMICOLON,
			eEQ = EQ,
			eLT = LT,
			eLEQ = LEQ,
			eGT = GT,
			eGEQ = GEQ,
			eNEQ = NEQ,
			eEQEQ = EQEQ,
			eLOGIC_AND = LOGIC_AND,
			eLOGIC_OR = LOGIC_OR,
			eLOGIC_NOT = LOGIC_NOT,
			eASS_MUL = ASS_MUL,
			eASS_DIV = ASS_DIV,
			eASS_MOD = ASS_MOD,
			eASS_PLUS = ASS_PLUS,
			eASS_MINUS = ASS_MINUS,
			eASS_SHR = ASS_SHR,
			eASS_SHL = ASS_SHL,
			eASS_AND = ASS_AND,
			eASS_OR = ASS_OR,
			eASS_XOR = ASS_XOR,
			eAND = AND,
			eOR = OR,
			eXOR = XOR,
			ePLUS = PLUS,
			eMINUS = MINUS,
			eNOT = NOT,
			eDIV = DIV,
			eMUL = MUL,
			eMOD = MOD,
			eSHR = SHR,
			eSHL = SHL,
			eID = ID,
			eLEFT_CURL_BRACKET = LEFT_CURL_BRACKET,
			eRIGHT_CURL_BRACKET = RIGHT_CURL_BRACKET,
			eLEFT_BRACKET = LEFT_BRACKET,
			eRIGHT_BRACKET = RIGHT_BRACKET,
			eLEFT_PAREN = LEFT_PAREN,
			eRIGHT_PAREN = RIGHT_PAREN,
			eUNION = UNION,
			eCHOICE = CHOICE,
			eON = ON,
			eCASE = CASE,
			eIF = IF,
			eFUNCTION = FUNCTION,
			eALIGN = ALIGN,
			eSIZEOF = SIZEOF,
			eBITSIZEOF = BITSIZEOF,
			eLENGTHOF = LENGTHOF,
			eIS = IS,
			eSUM = SUM,
			eQUESTION = QUESTION,
			eFORALL = FORALL,
			ePACKAGE = PACKAGE,
			eIMPORT = IMPORT,
			eDOT = DOT,
			eEND_OF_FILE = END_OF_FILE,
			eUNTERMINATED_STRING = UNTERMINATED_STRING,
			eUNKNOWN_LEXEME = UNKNOWN_LEXEME,
			eIO_ERROR = IO_ERROR
		};

		const char* token_to_string (token_t token);
		DATASCRIPT_API std::ostream& operator << (std::ostream& os, token_t token);
	} // ns scanner
} // ns datascript

#endif
