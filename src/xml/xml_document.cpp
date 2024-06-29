/*
 * xml_document.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include <fstream>
#include <libxml/tree.h>
#include <spdlog/spdlog.h>

#include "xml/xml_document.hpp"

using namespace piper;

xml_document::xml_document()
{
	_doc = nullptr;
	_valid = false;
}

xml_document::~xml_document()
{
	if (_doc)
		xmlFreeDoc(_doc);
}

bool
xml_document::is_valid() const
{
	return _valid;
}

bool
xml_document::load_from_buffer(const char *buf,
                               std::size_t len)
{
	spdlog::trace("Loading XML document from buffer.");
	_valid = false;
	if (_doc)
		xmlFreeDoc(_doc); // free existing document for overwrite
	_doc = xmlReadMemory(buf, len, nullptr, nullptr, 0);
	if (!_doc)
	{
		spdlog::error("Failed to parse XML document.");
		return false;
	}
	spdlog::trace("XML document load complete.");
	_valid = true;
	return true;
}

bool
xml_document::load_from_file(const std::filesystem::path &path)
{
	spdlog::trace("Reading XML document from file.");
	std::ifstream is(path, std::ios::binary | std::ios::ate);
	_valid = false;
	if (!is.is_open())
	{
		spdlog::error("File not found: '{}'", path.string());
		return false;
	}
	auto len = is.tellg();
	char *buf = new (std::nothrow) char[len];
	if (!buf)
		abort(); // out of memory
	is.seekg(0, std::ios::beg);
	is.read(buf, len);
	bool success = !!is;
	if (success)
		// read was successful, now try and load the buffer
		success = load_from_buffer(buf, len);
	else
		spdlog::error("Failed to read past byte #{}.", is.gcount());
	delete[] buf;
	return success;
}

bool
xml_document::load_from_string(const std::string &buf)
{
	spdlog::trace("Loading XML document from string.");
	_valid = false;
	return load_from_buffer(buf.c_str(), buf.length());
}
