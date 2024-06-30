/*
 * xml_node_comment.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_NODE_COMMENT_HPP
#define ZMQ_XML_THREAD_POC_XML_NODE_COMMENT_HPP

#include <string>

#include "xml/node/xml_node.hpp"

namespace piper
{

	class xml_node_comment : public xml_node
	{
	public:
		xml_node_comment(const std::string &comment);
		~xml_node_comment() = default;

		friend class xml_node;

		std::string comment    () const;
		void        set_comment(const std::string &comment);

	private:
		xml_node_comment(xmlNodePtr node);
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_NODE_COMMENT_HPP
