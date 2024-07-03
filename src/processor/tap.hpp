/*
 * tap.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_TAP_HPP
#define ZMQ_XML_THREAD_POC_TAP_HPP

#include "processor/node.hpp"

namespace piper
{

	class tap : public node
	{
	public:
		using node::node;
		~tap() = default;

	private:
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_TAP_HPP
