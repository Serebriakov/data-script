#include <sstream>
#include <stdexcept>
#include <iostream>

#include "datascript/syntax_tree.hpp"

namespace datascript
{

	namespace grammar
	{

		qualified_name::qualified_name ()
		{

		}
		// ---------------------------------------------------------------------------------
		bool qualified_name::empty () const
		{
			return m_components.empty ();
		}
		// ---------------------------------------------------------------------------------
		std::size_t qualified_name::size () const
		{
			return m_components.size ();
		}
		// ---------------------------------------------------------------------------------
		const std::string& qualified_name::operator [] (std::size_t index) const
		{
			if (m_components.size () <= index)
			{
				std::ostringstream os;
				os << "qualified name component index is out of range. #components = " << m_components.size () << " index = " << index << std::endl;
				throw std::out_of_range (os.str ().c_str ());
			}
			return m_components[index];
		}
		// =================================================================================
		std::ostream& operator << (std::ostream& os, const qualified_name& x)
		{
			const std::size_t n = x.size ();
			for (std::size_t i = 0; i < n; i++)
			{
				os << x[i];
				if (i < n - 1)
				{
					os << ".";
				}
			}
			return os;
		}
		// =================================================================================
		qualified_name_builder::qualified_name_builder (qualified_name& subject, std::size_t reserve)
			: m_subject (subject)
		{
			m_subject.m_components.reserve (reserve);
		}
		// ----------------------------------------------------------------------------------
		void qualified_name_builder::operator () (const char* string)
		{
			if (string == 0)
			{
				throw std::invalid_argument ("NULL passed to qualified_name_builder");
			}
			m_subject.m_components.push_back (string);
		}
		// ----------------------------------------------------------------------------------
		void qualified_name_builder::operator () (const char* start, const char* end)
		{
			if (start == 0)
			{
				throw std::invalid_argument ("NULL passed to qualified_name_builder");
			}

			if (end == 0)
			{
				m_subject.m_components.push_back (start);
			}
			else
			{
				m_subject.m_components.push_back (std::string (start, end));
			}
		}
		// ==================================================================================
		package_syntax_tree_builder::package_syntax_tree_builder (syntax_tree& subject, std::size_t reserve)
			: qualified_name_builder (subject.m_package, reserve)
		{

		}
		// ==================================================================================
		syntax_tree::syntax_tree ()
		{

		}
		// ----------------------------------------------------------------------------------
		syntax_tree::~syntax_tree ()
		{

		}
		// ----------------------------------------------------------------------------------
		const qualified_name& syntax_tree::package () const
		{
			return m_package;
		}
		// ---------------------------------------------------------------------------------
		
	} // ns grammar
} // ns datascript
