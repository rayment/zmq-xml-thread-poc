/*
 * sink_file.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 03/07/2024
 */

#include <cassert>

#include "processor/sinks/sink_file.hpp"

using namespace piper;

sink_file::sink_file(const piper::uuid &id) :
	sink(id)
{
	_append = false;
	_open = false;
}

sink_file::~sink_file()
{
	_stream.close();
}

bool
sink_file::append() const
{
	return _append;
}

const std::filesystem::path &
sink_file::filename() const
{
	return _path;
}

bool
sink_file::_open_stream()
{
	assert(!_open);
	auto flags = std::ios::binary | std::ios::out;
	if (_append)
		flags |= std::ios::app;
	_stream = std::ofstream(_path, flags);
	_open = _stream && _stream.is_open();
	return _open;
}

node_response
sink_file::process(const piper::node_message message)
{
	if (!_open && !_open_stream())
	{
		return node_response(
			pipe_connection_type::Error,
			{std::make_shared<std::string>(
				"Could not open sink file for write.")});
	}
	_stream.write(message->c_str(), message->length());
	if (!_stream)
	{
		return node_response(
			pipe_connection_type::Error,
			{std::make_shared<std::string>(
				"Incomplete write while trying to write to file sink.")});
	}
	return node_response(pipe_connection_type::Out, {});
}

void
sink_file::set_append(bool append)
{
	assert(!_stream.is_open());
	_append = append;
}

void
sink_file::set_filename(const std::filesystem::path &filename)
{
	assert(!_stream.is_open());
	_path = filename;
}
