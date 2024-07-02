/*
 * xml_schema.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include <libxml/xmlschemas.h>
#include <spdlog/spdlog.h>

#include "util/file_io.hpp"
#include "xml/xml_document.hpp"
#include "xml/xml_schema.hpp"

using namespace piper;

xml_schema::xml_schema()
{
	_schema = nullptr; // prevent _reset from performing undefined free
	_reset();
}

xml_schema::~xml_schema()
{
	_reset();
}

void
xml_schema::_context_error_handler(void *data,
                                   const xmlError *error)
{
	xml_schema *schema = static_cast<xml_schema *>(data);
	schema->_errors.push_back(xml_error_message(
		xml_error::ParseError,
		error->message));
}

void
xml_schema::_reset()
{
	if (_schema)
		xmlSchemaFree(_schema);
	_errors.clear();
	_schema = nullptr;
	_valid = false;
}

const std::vector<xml_error_message> &
xml_schema::errors() const
{
	return _errors;
}

bool
xml_schema::is_valid() const
{
	return _valid;
}

bool
xml_schema::load_from_buffer(const char *buf,
                             std::size_t len)
{
	spdlog::trace("Loading XML schema from buffer.");
	_reset();
	if (!_doc.load_from_buffer(buf, len))
	{
		auto doc_errors = _doc.errors();
		_errors.insert(_errors.end(), doc_errors.begin(), doc_errors.end());
		return false;
	}
	xmlSchemaParserCtxtPtr context = xmlSchemaNewDocParserCtxt(_doc._doc);
	if (!context)
	{
		_errors.push_back(xml_error_message(
			xml_error::InternalError,
			"Failed to generate XML schema parser context."));
		return false;
	}
	xmlSchemaSetParserStructuredErrors(context, _context_error_handler, this);
	_schema = xmlSchemaParse(context);
	xmlSchemaFreeParserCtxt(context);
	if (!_schema)
		return false; // error generation is handled by _context_error_handler
	spdlog::trace("XML schema load complete.");
	_valid = true;
	return true;
}

bool
xml_schema::load_from_file(const std::filesystem::path &path)
{
	spdlog::trace("Loading XML schema from file.");
	_reset();
	std::vector<char> buf;
	file_io_error read_err = file_read_to_buffer(path, buf);
	switch (read_err)
	{
	case FileNotFound:
		_errors.push_back(xml_error_message(
			xml_error::IOError,
			fmt::format("File not found: '{}'",
			            path.string())));
		break;
	case IncompleteRead:
		_errors.push_back(xml_error_message(
			xml_error::IOError,
			fmt::format("Failed to read XML schema from file '{}'",
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
xml_schema::load_from_string(const std::string &buf)
{
	spdlog::trace("Loading XML schema from string.");
	_reset();
	return load_from_buffer(buf.c_str(), buf.length());
}

bool
xml_schema::save_to_file(const std::filesystem::path &path) const
{
	return _doc.save_to_file(path);
}

std::string
xml_schema::save_to_string() const
{
	return _doc.save_to_string();
}
