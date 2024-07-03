/*
 * tap_file.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#include <cassert>

#include "processor/taps/tap_file.hpp"

using namespace piper;

tap_file::tap_file(const uuid &id) :
	tap(id)
{}

tap_file::~tap_file()
{}

const std::filesystem::path &
tap_file::filename() const
{
	return _path;
}

node_response
tap_file::process(const node_message message)
{
	(void) message;
	_stream = std::ifstream(_path, std::ios::binary);
	if (!_stream || !_stream.is_open())
	{
		return node_response(
			pipe_connection_type::Error,
			{std::make_shared<std::string>(
				"Could not open file tap for read.")});
	}
	node_message out = std::make_shared<std::string>();
	assert(out);
	std::stringstream buf;
	buf << _stream.rdbuf();
	if (!_stream)
	{
		return node_response(
			pipe_connection_type::Error,
			{std::make_shared<std::string>(
				"Incomplete read while trying to read from file tap.")});
	}
	_stream.close();
	*out = std::move(buf.str());
	close(); // nothing left for this node to do
	return node_response(pipe_connection_type::Out, {out});
}

void
tap_file::set_filename(const std::filesystem::path &filename)
{
	assert(!_stream.is_open());
	_path = filename;
}
