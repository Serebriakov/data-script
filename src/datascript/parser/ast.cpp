#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "datascript/parser/ast.h"
#include "datascript/scanner/tokens_storage.h"

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
	_qname (const std::string& c)
	{
		components.push_back (c);
	}

	_qname (const std::string& c, const _qname& other)
		: components (other.components)
	{
		components.push_front (c);
	}

	std::list <std::string> components;
};
// ----------------------------------------------------------------------------------
qname* qname_create (const parser_token* tok)
{
	return new _qname (token2string (tok));
}
// ----------------------------------------------------------------------------------
qname* qname_append (const parser_token* tok, qname* qn)
{
	return new _qname (token2string (tok), *qn);
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
	std::cout << "PACKAGE ";
	for (std::list <std::string>::const_iterator i = tok->components.begin (); i != tok->components.end (); i++)
	{
		std::cout << "<" << *i << ">";
	}
	std::cout << std::endl;
}
