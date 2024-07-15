/*
 * node.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 02/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_NODE_HPP
#define ZMQ_XML_THREAD_POC_NODE_HPP

#include <memory>
#include <vector>

#include "processor/pipe_connection_type.hpp"
#include "types/uuid.hpp"

namespace piper
{

	typedef std::shared_ptr<std::string> node_message;
	typedef std::pair<pipe_connection_type,
	                  std::vector<node_message>> node_response;

	class node
	{
	public:
		node(const uuid &id);
		virtual ~node() = 0;

		bool operator  <(const node &other) const;
		bool operator  >(const node &other) const;
		bool operator <=(const node &other) const;
		bool operator >=(const node &other) const;
		bool operator ==(const node &other) const;
		bool operator !=(const node &other) const;

		void                   close    ();
		const uuid            &id       () const;
		bool                   is_closed() const;
		node_response          process  ();
		virtual node_response  process  (const node_message message) = 0;

	private:
		bool _closed;
		const uuid _uuid;
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_NODE_HPP
