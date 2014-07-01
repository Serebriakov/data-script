#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "datascript/parser/parser_procs.h"
#include "datascript/scanner/tokens_storage.h"
#include "datascript/syntax_tree.hpp"

struct _ast
{
	datascript::grammar::syntax_tree* tree;
};

ast* ast_create ()
{
	ast* r = new ast;
	r->tree = new datascript::grammar::syntax_tree;
	return r;
}

void ast_free (ast* victim)
{
	delete victim;
}

void* ast_content (ast* obj)
{
	return obj->tree;
}

// ----------------------------------------------------------------------------------
static std::string token2string (const parser_token* tok)
{
	const char* s = 0;
	const char* e = 0;

	get_token_data (tok, &s, &e);
	if (s && !e)
	{
		return std::string (s);
	}
	if (s && e)
	{
		return std::string (s, e);
	}
	return "";
}
// ----------------------------------------------------------------------------------
struct _qname
{
	_qname (const parser_token* token)
		: car (token),
		  cdr (0), 
		  len (0)
	{
	}
	
	_qname (const parser_token* token, _qname* tail)
		: car (token),
		  cdr (tail),
		  len (1 + tail->len)
	{

	}

	~_qname ()
	{
		free_parser_token ((parser_token*)car);
		if (cdr)
		{
			delete cdr;
		}
	}
	
	const parser_token* car;
	const _qname* cdr;
	int len;
};
// ----------------------------------------------------------------------------------
qname* qname_create (const parser_token* tok)
{
	return new _qname (tok);
}
// ----------------------------------------------------------------------------------
qname* qname_append (const parser_token* tok, qname* qn)
{
	return new _qname (tok, qn);
}
// ----------------------------------------------------------------------------------
void qname_free (qname* victim)
{
	delete victim;
}
// ----------------------------------------------------------------------------------
// ==================================================================================
void ast_define_package (struct _ast* ast, const qname* tok)
{
	datascript::grammar::package_syntax_tree_builder builder (*ast->tree, (std::size_t)tok->len);

	const qname* current = tok;
	while (current)
	{
		const parser_token* car = current->car;
		const char* s = 0;
		const char* e = 0;

		get_token_data (car, &s, &e);
		builder (s, e);
		current = current->cdr;
	}
	delete tok;
	std::cout << "PACKAGE: " << ast->tree->package () << std::endl;
}
// ------------------------------------------------------------------------------------
void ast_import (struct _ast* ast, const qname* name)
{
	datascript::grammar::qualified_name qn;

	datascript::grammar::qualified_name_builder builder (qn, (std::size_t)name->len);

	const qname* current = name;
	while (current)
	{
		const parser_token* car = current->car;
		const char* s = 0;
		const char* e = 0;

		get_token_data (car, &s, &e);
		builder (s, e);
		current = current->cdr;
	}
	delete name;
	std::cout << "IMPORT: " << qn << std::endl;
}