/*
 * xml_node.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#include <cassert>
#include <spdlog/spdlog.h>

#include "xml/node/xml_node.hpp"
#include "xml/node/xml_node_element.hpp"

using namespace piper;

xml_node::xml_node()
{
	_node = nullptr;
}

xml_node::~xml_node()
{
	if (_node && _node->parent == nullptr)
		xmlFreeNode(_node); // death without an associated document
}

const std::vector<xml_node>
xml_node::children() const
{
	assert(_node != nullptr);
	std::vector<xml_node> children;
	xmlNodePtr tree = _node->children;
	while (tree)
	{
		switch (tree->type)
		{
		case XML_ELEMENT_NODE:
			children.push_back(xml_node_element(tree));
			break;
		}
		tree = tree->next;
	}
	return std::move(children);
}

bool
xml_node::is_element() const
{
	assert(_node != nullptr);
	return _node->type == XML_ELEMENT_NODE;
}

const std::string
xml_node::name() const
{
	assert(_node != nullptr);
	return std::string(reinterpret_cast<const char *>(_node->name));
}

void
xml_node::set_name(const std::string &name)
{
	assert(_node != nullptr);
	xmlNodeSetName(_node, reinterpret_cast<const xmlChar *>(name.c_str()));
}

void
xml_node::set_parent(xml_node &parent)
{
	assert(_node != nullptr);
	auto ptr = xmlAddChild(parent._node, _node);
	assert(ptr != nullptr);
}

void
xml_node::set_value(const std::string &value)
{
	assert(_node != nullptr);
	int ret = xmlNodeSetContent(_node, nullptr);
	assert(ret == 0);
	ret = xmlNodeAddContent(
		_node,
		reinterpret_cast<const xmlChar *>(value.c_str())
	);
	assert(ret == 0);
}

const std::string
xml_node::value() const
{
	assert(_node != nullptr);
	xmlNodePtr tree = _node->children;
	while (tree)
	{
		if (tree->type != XML_TEXT_NODE)
		{
			tree = tree->next;
			continue;
		}
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
	return std::string();
}
