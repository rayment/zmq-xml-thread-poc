/*
 * xml_document.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include <fstream>
#include <libxml/tree.h>
#include <spdlog/spdlog.h>

#include "util/file_io.hpp"
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
	std::vector<char> buf;
	bool fail = !file_read_to_buffer(path, buf);
	if (!fail)
		fail = !load_from_buffer(buf.data(), buf.size());
	return !fail;
}

bool
xml_document::load_from_string(const std::string &buf)
{
	spdlog::trace("Loading XML document from string.");
	_valid = false;
	return load_from_buffer(buf.c_str(), buf.length());
}
