/*
 * xml_node_element.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_NODE_ELEMENT_HPP
#define ZMQ_XML_THREAD_POC_XML_NODE_ELEMENT_HPP

#include <map>
#include <string>

#include "xml/node/xml_node.hpp"

namespace piper
{

	class xml_node_element : public xml_node
	{
	public:
		xml_node_element(const std::string &name);
		~xml_node_element() = default;

		friend class xml_document;
		friend class xml_node;

		const std::map<std::string, std::string>
		                  attributes      () const;
		const std::string name            () const;
		void              remove_attribute(const std::string &key);
		void              set_attribute   (const std::string &key,
		                                   const std::string &value);
		void              set_name        (const std::string &name);
		std::string       text            () const;

	private:
		xml_node_element(xmlNodePtr node);
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_NODE_ELEMENT_HPP
