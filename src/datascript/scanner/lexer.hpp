#ifndef __DATASCRIPT_PARSER_LEXER_HPP__
#define __DATASCRIPT_PARSER_LEXER_HPP__

#include <stdio.h>

#include "datascript/datascript_api.h"
#include "datascript/scanner/lexeme.hpp"

struct scanstate;

DATASCRIPT_SCANNER_NS_BEGIN

class DATASCRIPT_API lexer
{
public:
	enum
	{
		DEFAULT_BUFFER_LENGTH = 8192
	};

	typedef const char* char_ptr_t;
public:
  explicit lexer (FILE* f);
  explicit lexer (const char* string);

  ~lexer ();
  token_t scan (char_ptr_t& begin, char_ptr_t& end);
private:
	scanstate* ss;
};

DATASCRIPT_SCANNER_NS_END
#endif
