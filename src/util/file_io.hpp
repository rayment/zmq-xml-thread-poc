/*
 * file_io.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_FILE_IO_HPP
#define ZMQ_XML_THREAD_POC_FILE_IO_HPP

#include <cstddef>
#include <filesystem>
#include <vector>

namespace piper
{

	bool file_read_to_buffer(const std::filesystem::path &path,
							 std::vector<char> &buf);

} // piper

#endif //ZMQ_XML_THREAD_POC_FILE_IO_HPP
