/*
 * xml_node.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#include <cassert>
#include <spdlog/spdlog.h>

#include "xml/xml_node.hpp"

using namespace piper;

xml_node::xml_node(const std::string &name)
{
	_node = xmlNewDocNode(
		nullptr,
		nullptr,
		reinterpret_cast<const xmlChar *>(name.c_str()),
		nullptr
	);
	assert(_node != nullptr);
}

xml_node::xml_node(xmlNodePtr node)
{
	// Do not move getters to the ctor.
	// Preference is to generate dynamically upon request, particularly as the
	// attributes or children may change.
	assert(node != nullptr);
	_node = node;
}

const std::map<std::string, std::string>
xml_node::attributes() const
{
	std::map<std::string, std::string> attribs;
	xmlAttrPtr attribute = _node->properties;
	while (attribute)
	{
		xmlChar *out = xmlGetProp(_node, attribute->name);
		if (out)
		{
			attribs.insert(std::pair<std::string, std::string>(
				reinterpret_cast<const char *>(attribute->name),
				reinterpret_cast<const char *>(out)
			));
			xmlFree(out);
		}
		attribute = attribute->next;
	}
	return attribs;
}

const std::vector<xml_node>
xml_node::children() const
{
	std::vector<xml_node> children;
	xmlNodePtr tree = _node->children;
	while (tree)
	{
		if (tree->type == XML_ELEMENT_NODE)
			children.push_back(xml_node(tree));
		tree = tree->next;
	}
	return std::move(children);
}

const std::string
xml_node::name() const
{
	return std::string(reinterpret_cast<const char *>(_node->name));
}

const std::string
xml_node::value() const
{
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

void
xml_node::set_attribute(const std::string &key,
                        const std::string &value)
{
	xmlSetProp(_node,
	           reinterpret_cast<const xmlChar *>(key.c_str()),
	           reinterpret_cast<const xmlChar *>(value.c_str()));
}

void
xml_node::set_name(const std::string &name)
{
	xmlNodeSetName(_node, reinterpret_cast<const xmlChar *>(name.c_str()));
}

void
xml_node::set_parent(xml_node &parent)
{
	auto ptr = xmlAddChild(parent._node, _node);
	assert(ptr != nullptr);
}

void
xml_node::set_value(const std::string &value)
{
	int ret = xmlNodeSetContent(_node, nullptr);
	assert(ret == 0);
	ret = xmlNodeAddContent(
		_node,
		reinterpret_cast<const xmlChar *>(value.c_str())
	);
	assert(ret == 0);
}
