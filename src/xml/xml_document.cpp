/*
 * xml_document.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include <fmt/format.h>
#include <fstream>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/tree.h>
#include <spdlog/spdlog.h>

#include "util/file_io.hpp"
#include "xml/xml_document.hpp"

using namespace piper;

xml_document::xml_document()
{
	_doc = nullptr; // prevent _reset from performing undefined free
	_reset();
}

xml_document::~xml_document()
{
	_reset();
}

void
xml_document::_context_error_handler(void *data,
									 const xmlError *error)
{
	xml_document *doc = static_cast<xml_document *>(data);
	doc->_errors.push_back(xml_error_message(ParseError, error->message));
}

void
xml_document::_dump_to_buffer(xmlChar **buf,
                              int *len) const
{
	assert(!!buf && !!len);
	xmlDocDumpFormatMemoryEnc(_doc, buf, len, "utf-8", 1);
	if (!buf)
	{
		// failed memory allocation
		assert("Unexpected error. Aborting..." && false);
		// unreachable
		abort();
	}
}

void
xml_document::_reset()
{
	if (_doc)
		xmlFreeDoc(_doc);
	_doc = nullptr;
	_errors.clear();
	_valid = false;
}

const std::vector<xml_error_message> &
xml_document::errors() const
{
	return _errors;
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
	_reset();
	xmlInitParser();
	xmlParserCtxtPtr context = xmlCreateMemoryParserCtxt(buf, len);
	if (!context)
	{
		_errors.push_back(xml_error_message(
			InternalError,
			"Failed to generate XML parser context."));
		return false;
	}
	xmlCtxtSetErrorHandler(context, _context_error_handler, this);
	_doc = xmlCtxtReadMemory(context, buf, len, nullptr, nullptr, 0);
	if (!_doc)
		return false; // error generation is handled by _context_error_handler
	spdlog::trace("XML document load complete.");
	_valid = true;
	return true;
}

bool
xml_document::load_from_file(const std::filesystem::path &path)
{
	spdlog::trace("Loading XML document from file.");
	_reset();
	std::vector<char> buf;
	file_io_error read_err = file_read_to_buffer(path, buf);
	switch (read_err)
	{
	case FileNotFound:
		_errors.push_back(xml_error_message(
			IOError,
			fmt::format("File not found: '{}'",
			            path.string())));
		break;
	case IncompleteRead:
		_errors.push_back(xml_error_message(
			IOError,
			fmt::format("Failed to read XML document from file '{}'",
			            path.string())));
		break;
	case BadDestinationBuffer:
		assert("Unexpected error. Aborting..." && false);
		// unreachable
		abort();
	case None:
		return load_from_buffer(buf.data(), buf.size());
	}
	return false;
}

bool
xml_document::load_from_string(const std::string &buf)
{
	spdlog::trace("Loading XML document from string.");
	_reset();
	return load_from_buffer(buf.c_str(), buf.length());
}

bool
xml_document::save_to_file(const std::filesystem::path &path) const
{
	xmlChar *buf;
	int len;
	_dump_to_buffer(&buf, &len);
	file_write_from_buffer(
		path,
		std::vector<char>(buf, buf+len),
		false
	);
	xmlFree(buf);
	return true;
}

std::string
xml_document::save_to_string() const
{
	xmlChar *buf;
	int len;
	_dump_to_buffer(&buf, &len);
	std::string result = std::string(reinterpret_cast<char *>(buf), len);
	xmlFree(buf);
	return std::move(result);
}
