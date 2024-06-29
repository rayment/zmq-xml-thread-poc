/*
 * xml_document.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_XML_DOCUMENT_HPP
#define ZMQ_XML_THREAD_POC_XML_DOCUMENT_HPP

#include <cstddef>
#include <filesystem>
#include <libxml/tree.h>
#include <libxml/xmlerror.h>
#include <string>
#include <vector>

#include "xml/xml_error.hpp"
#include "xml/xml_node.hpp"

namespace piper
{

	class xml_document
	{
	public:
		xml_document();
		~xml_document();

		friend class xml_schema;
		friend class xml_validator;

		const std::vector<xml_error_message> &
		            errors          () const;
		bool        is_valid        () const;
		bool        load_from_buffer(const char *buf, std::size_t len);
		bool        load_from_file  (const std::filesystem::path &path);
		bool        load_from_string(const std::string &buf);
		xml_node    root_node       ();
		bool        save_to_file    (const std::filesystem::path &path) const;
		std::string save_to_string  () const;
	private:
		xmlDocPtr                      _doc;
		std::vector<xml_error_message> _errors;
		bool                           _valid;

		static void _context_error_handler(void *data, const xmlError *error);
		void        _dump_to_buffer(xmlChar **buf, int *len) const;
		void        _reset();
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_XML_DOCUMENT_HPP
