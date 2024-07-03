/*
 * sink.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 03/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_SINK_HPP
#define ZMQ_XML_THREAD_POC_SINK_HPP

#include "processor/node.hpp"

namespace piper
{

	class sink : public node
	{
	public:
		using node::node;
		~sink() = default;

	private:
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_SINK_HPP
