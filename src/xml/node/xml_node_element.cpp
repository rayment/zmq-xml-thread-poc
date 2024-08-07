/*
 * xml_node_element.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 30/06/2024
 */

#include <cassert>
#include <libxml/tree.h>

#include "xml/node/xml_node_element.hpp"

using namespace piper;

xml_node_element::xml_node_element(const std::string &name)
{
	_node = xmlNewDocNode(
		nullptr,
		nullptr,
		reinterpret_cast<const xmlChar *>(name.c_str()),
		nullptr
	);
	assert(_node != nullptr);
}

xml_node_element::xml_node_element(xmlNodePtr node)
{
	assert(node != nullptr);
	assert(node->type == XML_ELEMENT_NODE);
	_node = node;
}

const std::map<std::string, std::string>
xml_node_element::attributes() const
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

const std::string
xml_node_element::name() const
{
	return std::string(reinterpret_cast<const char *>(_node->name));
}

void
xml_node_element::remove_attribute(const std::string &key)
{
	const xmlChar *name = reinterpret_cast<const xmlChar *>(key.c_str());
	xmlAttrPtr prop = xmlHasProp(_node, name);
	if (prop)
	{
		assert(prop->parent != nullptr);
		xmlRemoveProp(prop);
	}
}

void
xml_node_element::set_attribute(const std::string &key,
                                const std::string &value)
{
	xmlSetProp(_node,
	           reinterpret_cast<const xmlChar *>(key.c_str()),
	           reinterpret_cast<const xmlChar *>(value.c_str()));
}

void
xml_node_element::set_name(const std::string &name)
{
	xmlNodeSetName(_node, reinterpret_cast<const xmlChar *>(name.c_str()));
}

std::string
xml_node_element::text() const
{
	// Same as in xml_node_text only that this will gather all child nodes.
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
