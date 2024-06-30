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
#include "xml/node/xml_node_text.hpp"

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
		case XML_TEXT_NODE:
			children.push_back(xml_node_text(tree));
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

bool
xml_node::is_text() const
{
	assert(_node != nullptr);
	return _node->type == XML_TEXT_NODE;
}

void
xml_node::set_parent(xml_node &parent)
{
	assert(_node != nullptr);
	auto ptr = xmlAddChild(parent._node, _node);
	assert(ptr != nullptr);
}
