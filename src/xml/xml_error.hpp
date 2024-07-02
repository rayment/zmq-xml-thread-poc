/*
 * xml_error.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_ERROR_HPP
#define ZMQ_XML_THREAD_POC_XML_ERROR_HPP

#include <string>

#include "util/error_message.hpp"

namespace piper
{

	enum class xml_error
	{
		// NOTE: Update code_string() whenever adding a new error.
		IOError,
		InternalError,
		InvalidDocumentError,
		InvalidSchemaError,
		ParseError,
		ValidationError,
	};

	class xml_error_message : public error_message<xml_error>
	{
	public:
		using error_message<xml_error>::error_message;
		using error_message<xml_error>::operator=;

		virtual const std::string
		code_string() const override
		{
			switch (_code)
			{
			case xml_error::IOError:              return "IOError";
			case xml_error::InternalError:        return "InternalError";
			case xml_error::InvalidDocumentError: return "InvalidDocumentError";
			case xml_error::InvalidSchemaError:   return "InvalidSchemaError";
			case xml_error::ParseError:           return "ParseError";
			case xml_error::ValidationError:      return "ValidationError";
			default:                              return "Unknown";
			}
		}
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_ERROR_HPP
