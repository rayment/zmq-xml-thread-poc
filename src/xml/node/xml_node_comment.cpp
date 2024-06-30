/*
 * xml_node_comment.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#include <cassert>
#include <libxml/tree.h>

#include "xml/node/xml_node_comment.hpp"

using namespace piper;

xml_node_comment::xml_node_comment(const std::string &comment)
{
	_node = xmlNewDocComment(
		nullptr,
		reinterpret_cast<const xmlChar *>(comment.c_str())
	);
	assert(_node != nullptr);
}

xml_node_comment::xml_node_comment(xmlNodePtr node)
{
	assert(node != nullptr);
	assert(node->type == XML_COMMENT_NODE);
	_node = node;
}

std::string
xml_node_comment::comment() const
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
xml_node_comment::set_comment(const std::string &comment)
{
	int ret = xmlNodeSetContent(_node, nullptr);
	assert(ret == 0);
	ret = xmlNodeAddContent(
		_node,
		reinterpret_cast<const xmlChar *>(comment.c_str())
	);
	assert(ret == 0);
}
