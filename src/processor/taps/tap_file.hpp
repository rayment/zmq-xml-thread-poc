/*
 * tap_file.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_TAP_FILE_HPP
#define ZMQ_XML_THREAD_POC_TAP_FILE_HPP

#include <filesystem>
#include <fstream>

#include "processor/tap.hpp"

namespace piper
{

	class tap_file : public tap
	{
	public:
		tap_file(const uuid &id);
		~tap_file();

		using node::process;

		const std::filesystem::path &
		              filename    () const;
		node_response process     (const node_message message) override;
		void          set_filename(const std::filesystem::path &filename);

	private:
		std::filesystem::path _path;
		std::ifstream         _stream;
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_TAP_FILE_HPP
