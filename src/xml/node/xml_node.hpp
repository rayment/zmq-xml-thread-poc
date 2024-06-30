/*
 * xml_node.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_NODE_HPP
#define ZMQ_XML_THREAD_POC_XML_NODE_HPP

#include <libxml/tree.h>
#include <map>
#include <string>
#include <vector>

namespace piper
{

	class xml_node
	{
	public:
		virtual ~xml_node();

		friend class xml_document;

		const std::vector<xml_node> children  () const;
		bool                        is_cdata  () const;
		bool                        is_comment() const;
		bool                        is_element() const;
		bool                        is_text   () const;
		void                        set_parent(xml_node &parent);

	protected:
		xmlNodePtr _node;

		xml_node();
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_NODE_HPP
