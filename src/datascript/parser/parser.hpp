#ifndef __DATASCRIPT_PARSER_H__
#define __DATASCRIPT_PARSER_H__

#include "datascript/datascript_api.h"
#include "datascript/scanner/lexeme.hpp"

struct _parser_token;

DATASCRIPT_SCANNER_NS_BEGIN

class DATASCRIPT_API parser 
{
 public:
  parser ();
  ~parser ();

  void operator () (token_t token, _parser_token* pt);
  void finish ();
  void enable_debug (FILE* fp, const char* prefix);
 private:
  parser (const parser& );
  parser& operator = (const parser& );
 private:
  void* m_lemon_parser;
};

DATASCRIPT_SCANNER_NS_END

#endif
