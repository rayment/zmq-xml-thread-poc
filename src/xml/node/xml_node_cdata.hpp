/*
 * xml_node_cdata.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_NODE_CDATA_HPP
#define ZMQ_XML_THREAD_POC_XML_NODE_CDATA_HPP

#include <map>
#include <string>

#include "xml/node/xml_node.hpp"

namespace piper
{

	class xml_node_cdata : public xml_node
	{
	public:
		xml_node_cdata(const std::string &data);
		~xml_node_cdata() = default;

		friend class xml_node;

		std::string data    () const;
		void        set_data(const std::string &data);

	private:
		xml_node_cdata(xmlNodePtr node);
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_NODE_CDATA_HPP
