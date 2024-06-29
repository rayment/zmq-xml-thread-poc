/*
 * xml_error.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include "xml/xml_error.hpp"

using namespace piper;

xml_error_message::xml_error_message(piper::xml_error code,
                                     const std::string &msg) :
	_code(code), _message(msg)
{}

xml_error
xml_error_message::code() const
{
	return _code;
}

const std::string
xml_error_message::code_string() const
{
	switch (_code)
	{
	case IOError:              return "IOError";
	case InternalError:        return "InternalError";
	case InvalidDocumentError: return "InvalidDocumentError";
	case InvalidSchemaError:   return "InvalidSchemaError";
	case ParseError:           return "ParseError";
	case ValidationError:      return "ValidationError";
	default:                   return "Unknown";
	}
}

const std::string &
xml_error_message::message() const
{
	return _message;
}
