/*
 * xml_node_cdata.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#include <cassert>
#include <libxml/tree.h>

#include "xml/node/xml_node_cdata.hpp"

using namespace piper;

xml_node_cdata::xml_node_cdata(const std::string &data)
{
	_node = xmlNewCDataBlock(
		nullptr,
		reinterpret_cast<const xmlChar *>(data.c_str()),
		data.length()
	);
	assert(_node != nullptr);
}

xml_node_cdata::xml_node_cdata(xmlNodePtr node)
{
	assert(node != nullptr);
	assert(node->type == XML_CDATA_SECTION_NODE);
	_node = node;
}

std::string
xml_node_cdata::data() const
{
	xmlChar *val = xmlNodeGetContent(_node);
	if (!val)
	{
		return std::string();
	}
	else
	{
		std::string str_val = reinterpret_cast<const char *>(val);
		xmlFree(val);
		return std::move(str_val);
	}
}

void
xml_node_cdata::set_data(const std::string &data)
{
	int ret = xmlNodeSetContent(_node, nullptr);
	assert(ret == 0);
	ret = xmlNodeAddContent(
		_node,
		reinterpret_cast<const xmlChar *>(data.c_str())
	);
	assert(ret == 0);
}
