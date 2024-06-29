/*
 * xml_schema.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_SCHEMA_HPP
#define ZMQ_XML_THREAD_POC_XML_SCHEMA_HPP

#include <cstddef>
#include <filesystem>
#include <libxml/xmlschemas.h>
#include <string>
#include <vector>

#include "xml/xml_error.hpp"

namespace piper
{

	class xml_schema
	{
	public:
		xml_schema();
		~xml_schema();

		const std::vector<xml_error_message> &
			errors           () const;
		bool is_valid        () const;
		bool load_from_buffer(const char *buf, std::size_t len);
		bool load_from_file  (const std::filesystem::path &path);
		bool load_from_string(const std::string &buf);
	private:
		std::vector<xml_error_message> _errors;
		xmlSchemaPtr                   _schema;
		bool                           _valid;

		static void _context_error_handler(void *data, const xmlError *error);
		void        _reset();
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_SCHEMA_HPP
