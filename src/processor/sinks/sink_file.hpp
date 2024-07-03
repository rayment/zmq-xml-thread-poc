/*
 * sink_file.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 03/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_SINK_FILE_HPP
#define ZMQ_XML_THREAD_POC_SINK_FILE_HPP

#include <filesystem>
#include <fstream>

#include "processor/sink.hpp"

namespace piper
{

	class sink_file : public sink
	{
	public:
		sink_file(const uuid &id);
		~sink_file();

		using node::process;

		bool          append      () const;
		const std::filesystem::path &
		              filename    () const;
		node_response process     (const node_message message) override;
		void          set_append  (bool append);
		void          set_filename(const std::filesystem::path &filename);

	private:
		bool                  _append;
		std::filesystem::path _path;
		std::ofstream         _stream;
		bool                  _open;

		bool                  _open_stream();
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_SINK_FILE_HPP
