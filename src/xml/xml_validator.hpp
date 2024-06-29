/*
 * xml_validator.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_VALIDATOR_HPP
#define ZMQ_XML_THREAD_POC_XML_VALIDATOR_HPP

#include "xml/xml_error.hpp"
#include "xml/xml_document.hpp"
#include "xml/xml_schema.hpp"

namespace piper
{

	class xml_validator
	{
	public:
		xml_validator();
		~xml_validator() = default;

		const std::vector<xml_error_message> &
			errors   () const;
		bool validate(xml_document &document, xml_schema &schema);
	private:
		std::vector<xml_error_message> _errors;

		static void _context_error_handler(void *data, const xmlError *error);
		void        _reset();
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_VALIDATOR_HPP
