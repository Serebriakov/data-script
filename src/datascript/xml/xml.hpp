#ifndef __DATASCRIPT_XML_HPP__
#define __DATASCRIPT_XML_HPP__

#include <list>
#include <string>
#include <sstream>

namespace datascript
{
    namespace xml
    {
        class attrib
        {
        public:
            template <typename T>
            attrib (const std::string name, const T& value);

            void print (std::ostream& os) const;
        private:
            std::string m_name;
            std::string m_value;
        };
        
        std::ostream& operator << (std::ostream& os, const attrib& attrib);
        // ===================================================================
        class node
        {
        public:
            node (const std::string& name);

            virtual ~node ();
            
            void append_attrib (const attrib& attr);
            void append_cdata (const std::string& data);

            std::ostringstream& cdata ();
            const std::ostringstream& cdata () const;

            void append_child (node* node);

            void print (std::ostream& os, size_t depth=0) const;

        private:
            typedef std::list<attrib>         attr_list_t;
            typedef attr_list_t::iterator       attr_iterator_t;
            typedef attr_list_t::const_iterator attr_const_iterator_t;

            typedef std::list<node*>       nodes_list_t;
            typedef nodes_list_t::iterator       nodes_iterator_t;
            typedef nodes_list_t::const_iterator nodes_const_iterator_t;
        private:
            std::string        m_name;
            std::ostringstream m_cdata;

            attr_list_t        m_attr;
            nodes_list_t       m_nodes;
        };

        node& operator << (node& n, const attrib& attrib);
        node& operator << (node& n, const std::string& cdata);
        node& operator << (node& n, node* other);
        std::ostream& operator << (std::ostream& os, const node& n);
    } // ns xml
} // ns datascript
// ===========================================================================
// Implementation
// ===========================================================================
namespace datascript
{
    namespace xml
    {
        template <typename T>
        inline
        attrib::attrib (const std::string name, const T& value)
            : m_name (name)
        {
            std::ostringstream s;
            s << value;
            m_value = s.str ();
        }
        // --------------------------------------------------------------------
        inline
        void attrib::print (std::ostream& os) const
        {
            os << m_name << "=\"" << m_value << "\"";
        }
        // --------------------------------------------------------------------
        inline
        std::ostringstream& node::cdata ()
        {
            return m_cdata;
        }
        // --------------------------------------------------------------------
        inline
        const std::ostringstream& node::cdata () const
        {
            return m_cdata;
        }
        // --------------------------------------------------------------------
        inline
        std::ostream& operator << (std::ostream& os, const attrib& attrib)
        {
            attrib.print (os);
            return os;
        }
        // --------------------------------------------------------------------
        inline
        node& operator << (node& n, const attrib& attrib)
        {
            n.append_attrib (attrib);
            return n;
        }
        // --------------------------------------------------------------------
        inline
        node& operator << (node& n, const std::string& cdata)
        {
            n.append_cdata (cdata);
            return n;
        }
        // --------------------------------------------------------------------
        inline
        node& operator << (node& n, node* other)
        {
            n.append_child (other);
            return n;
        }
        // --------------------------------------------------------------------
        inline
        std::ostream& operator << (std::ostream& os, const node& n)
        {
            n.print (os);
            return os;
        }
    } // ns xml
} // ns datascript

#endif
