#ifndef __DATASCRIPT_SYNTAX_TREE_HPP__
#define __DATASCRIPT_SYNTAX_TREE_HPP__

#include <string>
#include <vector>
#include <iosfwd>

#include "datascript/datascript_api.h"

DATASCRIPT_SCANNER_NS_BEGIN

class qualified_name_builder;

class DATASCRIPT_API qualified_name
{
	friend class qualified_name_builder;
public:
	qualified_name ();
	bool empty () const;
	std::size_t size () const;
	const std::string& operator [] (std::size_t index) const;
private:
#if defined(_MSC_VER)
#pragma warning ( push )
#pragma warning ( disable: 4251 )
#endif  
	std::vector <std::string> m_components;
#if defined(_MSC_VER)
#pragma warning ( pop )
#endif  
};

DATASCRIPT_API std::ostream& operator << (std::ostream& os, const qualified_name& x);
// ======================================================================
class qualified_name_builder
{
public:
	qualified_name_builder (qualified_name& subject, std::size_t reserve);

	void operator () (const char* string);
	void operator () (const char* start, const char* end);
private:
	qualified_name& m_subject;
};
// ======================================================================
class DATASCRIPT_API syntax_tree;

class package_syntax_tree_builder : public qualified_name_builder
{
public:
	package_syntax_tree_builder (syntax_tree& subject, std::size_t reserve);
};
// ======================================================================
class syntax_tree
{
	friend class package_syntax_tree_builder;
public:
	syntax_tree ();
	~syntax_tree ();

	const qualified_name& package () const;
private:
	qualified_name m_package;
};

DATASCRIPT_SCANNER_NS_END


#endif
