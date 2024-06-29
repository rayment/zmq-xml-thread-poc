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
		xml_node(const std::string &name);
		xml_node(xmlNodePtr node);
		~xml_node() = default;

		const std::map<std::string, std::string> attributes() const;
		const std::vector<xml_node>              children  () const;
		const std::string                        name      () const;
		const std::string                        value     () const;

		void set_attribute(const std::string &key, const std::string &value);
		void set_name     (const std::string &name);
		void set_parent   (xml_node &parent);
		void set_value    (const std::string &value);

	private:
		xmlNodePtr  _node;
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_NODE_HPP
