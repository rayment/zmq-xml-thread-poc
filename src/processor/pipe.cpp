/*
 * pipe.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#include "processor/pipe.hpp"

using namespace piper;

pipe::pipe()
{}

pipe::~pipe()
{}

const std::string &
pipe::author() const
{
	return _author;
}

const std::string &
pipe::description() const
{
	return _description;
}

pipe::pipe_graph &
pipe::graph()
{
	return _graph;
}

const std::string &
pipe::name() const
{
	return _name;
}

void
pipe::set_author(const std::string &author)
{
	_author = author;
}

void
pipe::set_description(const std::string &description)
{
	_description = description;
}

void
pipe::set_name(const std::string &name)
{
	_name = name;
}
