/*
 * pipe.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 29/06/2024
 */

#ifndef ZMQ_XML_THREAD_POC_PIPE_HPP
#define ZMQ_XML_THREAD_POC_PIPE_HPP

#include <string>
#include <vector>

#include "processor/node.hpp"
#include "processor/pipe_connection_type.hpp"
#include "types/multidigraph.hpp"
#include "types/uuid.hpp"

namespace piper
{

	class pipe
	{
	public:
		pipe();
		~pipe();

		typedef piper::multidigraph<std::unique_ptr<node>,
		                            pipe_connection_type> pipe_graph;

		const std::string &author           () const;
		const std::string &description      () const;
		pipe_graph        &graph            ();
		const std::string &name             () const;
		void               set_author       (const std::string &author);
		void               set_description  (const std::string &description);
		void               set_name         (const std::string &name);

	private:
		std::string       _author;
		std::string       _description;
		pipe_graph        _graph;
		std::string       _name;
	};

} // piper

#endif //ZMQ_XML_THREAD_POC_PIPE_HPP
