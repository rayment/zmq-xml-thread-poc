/*
 * file_io.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include <fstream>
#include <spdlog/spdlog.h>

#include "file_io.hpp"

using namespace piper;

file_io_error
piper::file_read_to_buffer(const std::filesystem::path &path,
                           std::vector<char> &buf)
{
	spdlog::trace("Reading file '{}' to buffer.", path.string());
	if (!buf.empty())
		return BadDestinationBuffer;
	std::ifstream fs(path, std::ios::binary | std::ios::ate);
	if (!fs.is_open())
		return FileNotFound;
	auto len = fs.tellg();
	buf.reserve(len);
	fs.seekg(0, std::ios::beg);
	buf.assign(std::istreambuf_iterator<char>(fs),
	           std::istreambuf_iterator<char>());
	bool success = !!fs;
	if (!success)
		return IncompleteRead;
	return None;
}
