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

bool
piper::file_read_to_buffer(const std::filesystem::path &path,
                           std::vector<char> &buf)
{
	spdlog::trace("Reading file '{}' to buffer.", path.string());
	if (!buf.empty())
	{
		spdlog::error("Refusing to read file into non-empty buffer.");
		return false;
	}
	std::ifstream fs(path, std::ios::binary | std::ios::ate);
	if (!fs.is_open())
	{
		spdlog::error("File not found: '{}'", path.string());
		return false;
	}
	auto len = fs.tellg();
	buf.reserve(len);
	fs.seekg(0, std::ios::beg);
	buf.assign(std::istreambuf_iterator<char>(fs),
	           std::istreambuf_iterator<char>());
	bool success = !!fs;
	if (!success)
		spdlog::error("Failed to read past byte #{}.", fs.gcount());
	return success;
}
