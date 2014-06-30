#ifndef __DATASCRIPT_PARSER_PROCS_H__
#define __DATASCRIPT_PARSER_PROCS_H__

struct _ast;
struct _parser_token;

typedef struct _ast ast;
typedef struct _parser_token parser_token;

#if defined(__cplusplus)
extern "C" {
#endif

	/* =============================================================== */
	/* QNAME API */
	/* =============================================================== */

	struct _qname;
	typedef struct _qname qname;

	qname* qname_create (const parser_token* tok);
	qname* qname_append (const parser_token* tok, qname* qn);

	void qname_free (qname* victim);
	/* =============================================================== */
	/* AST API */
	/* =============================================================== */
	
	ast* ast_create ();
	void ast_free (ast* victim);

	void* ast_content (ast* obj);

	void ast_define_package (struct _ast* ast, const qname* name);
	void ast_import (struct _ast* ast, const qname* name);

#if defined(__cplusplus)
}
#endif

#endif
