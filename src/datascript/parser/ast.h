#ifndef __DATASCRIPT_PARSER_AST_H__
#define __DATASCRIPT_PARSER_AST_H__

struct _ast;
struct _parser_token
{
  const char* begin;
  const char* end;
};

typedef struct _parser_token parser_token;

#if defined(__cplusplus)
extern "C" {
#endif

  void ast_define_package (struct _ast* ast, const parser_token* tok);


#if defined(__cplusplus)
}
#endif

#endif
