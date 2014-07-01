#include "datascript/xml/xml.hpp"

namespace datascript
{
    namespace xml
    {
        node::node (const std::string& name)
            : m_name (name)
        {
        }
        // ----------------------------------------------------------------------
        node::~node ()
        {
            for (nodes_iterator_t i=m_nodes.begin (); i!=m_nodes.end (); i++)
            {
                node* victim = *i;
                delete victim;
            }
        }
        // ----------------------------------------------------------------------
        void node::append_attrib (const attrib& attr)
        {
            m_attr.push_back (attr);
        }
        // ----------------------------------------------------------------------
        void node::append_cdata (const std::string& data)
        {
            m_cdata << data;
        }
        // ----------------------------------------------------------------------
        void node::append_child (node* node)
        {
            m_nodes.push_back (node);
        }
        // ----------------------------------------------------------------------
        void node::print (std::ostream& os, size_t depth) const
        {
            const std::string& c_data = m_cdata.str ();
            
            std::string tabs ("");
            if (depth > 0)
            {
                tabs.assign (depth, '\t');
            }
            
            os << tabs << "<" << m_name;

            if (!m_attr.empty ())
            {
                for (attr_const_iterator_t i=m_attr.begin (); i!=m_attr.end (); i++)
                {
                    os << " ";
                    i->print (os);
                }
            }
            
            if (m_nodes.empty () && c_data.empty ())
            {
                
                os << " />";
                return;
            }
            
            os << ">";
            if (!c_data.empty ())
            {
                os << "\n" << c_data << "\n";
            }
            if (!m_nodes.empty ())
            {
                os << "\n";
                for (nodes_const_iterator_t i=m_nodes.begin (); i!=m_nodes.end (); i++)
                {
                    node* node = *i;
                    node->print (os, depth + 1);
                    os << "\n";
                }
            }
            os << tabs << "</" << m_name << ">";
        }
        // ----------------------------------------------------------------------
    } // ns web
} // ns abl

