/*
 * xml_node_text.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#include <cassert>
#include <libxml/tree.h>

#include "xml/node/xml_node_text.hpp"

using namespace piper;

xml_node_text::xml_node_text(const std::string &data)
{
	_node = xmlNewDocText(
		nullptr,
		reinterpret_cast<const xmlChar *>(data.c_str())
	);
	assert(_node != nullptr);
}

xml_node_text::xml_node_text(xmlNodePtr node)
{
	assert(node != nullptr);
	assert(node->type == XML_TEXT_NODE);
	_node = node;
}

void
xml_node_text::set_text(const std::string &data)
{
	int ret = xmlNodeSetContent(_node, nullptr);
	assert(ret == 0);
	ret = xmlNodeAddContent(
		_node,
		reinterpret_cast<const xmlChar *>(data.c_str())
	);
	assert(ret == 0);
}

std::string
xml_node_text::text()
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
