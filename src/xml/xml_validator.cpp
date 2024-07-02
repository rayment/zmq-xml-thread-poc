/*
 * xml_validator.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include "xml/xml_validator.hpp"

using namespace piper;

xml_validator::xml_validator()
{
	_reset();
}

void
xml_validator::_context_error_handler(void *data,
                                      const xmlError *error)
{
	xml_validator *validator = static_cast<xml_validator*>(data);
	validator->_errors.push_back(
		xml_error_message(xml_error::ValidationError, error->message));
}

void
xml_validator::_reset()
{
	_errors.clear();
}

const std::vector<xml_error_message> &
xml_validator::errors() const
{
	return _errors;
}

bool
xml_validator::validate(piper::xml_document &document,
                        piper::xml_schema &schema)
{
	if (!document.is_valid())
	{
		_errors.push_back(xml_error_message(
			xml_error::InvalidDocumentError,
			"Cannot validate because the document is invalid."));
	}
	if (!schema.is_valid())
	{
		_errors.push_back(xml_error_message(
			xml_error::InvalidSchemaError,
			"Cannot validate because the schema is invalid."));
	}
	if (!document.is_valid() || !schema.is_valid())
		return false; // do this separately to allow accumulated errors
	xmlSchemaValidCtxtPtr context = xmlSchemaNewValidCtxt(schema._schema);
	if (!context)
	{
		_errors.push_back(xml_error_message(
			xml_error::InternalError,
			"Failed to generate XML validation context."));
		return false;
	}
	xmlSchemaSetValidStructuredErrors(context, _context_error_handler, this);
	int ret = xmlSchemaValidateDoc(context, document._doc);
	if (ret != 0)
		return false; // error generation is handled by _context_error_handler
	xmlSchemaFreeValidCtxt(context);
	return true;
}
