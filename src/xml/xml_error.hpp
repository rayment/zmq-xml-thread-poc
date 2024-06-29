/*
 * xml_error.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_ERROR_HPP
#define ZMQ_XML_THREAD_POC_XML_ERROR_HPP

#include <string>

namespace piper
{

	enum xml_error
	{
		// NOTE: Update code_string() whenever adding a new error.
		IOError,
		InternalError,
		InvalidDocumentError,
		InvalidSchemaError,
		ParseError,
		ValidationError,
	};

	class xml_error_message
	{
	public:
		xml_error_message(xml_error code, const std::string &msg);
		xml_error_message(const xml_error_message &other);
		~xml_error_message() = default;

		xml_error_message operator =(const xml_error_message &other);

		xml_error          code       () const;
		const std::string  code_string() const;
		const std::string &message    () const;

	private:
		const xml_error   _code;
		const std::string _message;
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_ERROR_HPP
