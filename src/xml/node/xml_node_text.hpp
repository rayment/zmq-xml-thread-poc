/*
 * xml_node_text.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_NODE_TEXT_HPP
#define ZMQ_XML_THREAD_POC_XML_NODE_TEXT_HPP

#include <map>
#include <string>

#include "xml/node/xml_node.hpp"

namespace piper
{

	class xml_node_text : public xml_node
	{
	public:
		xml_node_text(const std::string &data);
		~xml_node_text() = default;

		friend class xml_node;

		void set_text   (const std::string &data);
		std::string text();

	private:
		xml_node_text(xmlNodePtr node);
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_NODE_TEXT_HPP
