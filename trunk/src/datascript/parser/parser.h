#ifndef __DATASCRIPT_PARSER_H__
#define __DATASCRIPT_PARSER_H__

#include <stddef.h>
#ifndef NDEBUG
#include <stdio.h>
#endif

#include "datascript/parser/ast.h"


#if defined(__cplusplus)
extern "C" {
#endif



  void *datascript_parserAlloc(void *(*mallocProc)(size_t));

  void datascript_parserFree(
			      void *p,      /* The parser to be deleted */
			      void (*freeProc)(void*) /* Function used to reclaim memory */);
  
  void datascript_parser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  parser_token* yyminor,       /* The value for the token */
  struct _ast* ast               /* Optional %extra_argument parameter */
  );

#ifndef NDEBUG

  void datascript_parserTrace(FILE *TraceFILE, const char *zTracePrompt);

#endif

#if defined(__cplusplus)
}
#endif


#if defined(__cplusplus) && !defined(IN_LEMON)

#include "datascript/datascript_api.h"
#include "datascript/scanner/lexeme.hpp"

DATASCRIPT_SCANNER_NS_BEGIN

class DATASCRIPT_API parser 
{
 public:
  parser ();
  ~parser ();

  void operator () (token_t token, const char* begin, const char* end);
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

#endif