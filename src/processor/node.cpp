/*
 * node.cpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#include "processor/node.hpp"

using namespace piper;

node::node(const uuid &id) : _uuid(id)
{
	_closed = false;
}

node::~node()
{}

bool
node::operator <(const node &other) const
{
	return _uuid < other._uuid;
}

bool
node::operator >(const node &other) const
{
	return _uuid > other._uuid;
}

bool
node::operator <=(const node &other) const
{
	return _uuid <= other._uuid;
}


bool
node::operator >=(const node &other) const
{
	return _uuid >= other._uuid;
}

bool
node::operator ==(const node &other) const
{
	return _uuid == other._uuid;
}

bool
node::operator !=(const node &other) const
{
	return _uuid != other._uuid;
}

void
node::close()
{
	_closed = true;
}

const uuid &
node::id() const
{
	return _uuid;
}

bool
node::is_closed() const
{
	return _closed;
}

node_response
node::process()
{
	return process(nullptr);
}
