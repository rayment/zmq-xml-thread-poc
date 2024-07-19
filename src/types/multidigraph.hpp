/*
 * multidigraph.hpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 08/07/2024
 */

#ifndef ZMQ_XML_THREAD_POC_MULTIDIGRAPH_HPP
#define ZMQ_XML_THREAD_POC_MULTIDIGRAPH_HPP

#include <algorithm>
#include <list>
#include <memory>
#include <optional>
#include <vector>

#include "util/sfinae.hpp"

namespace piper
{

	template<typename V, typename E>
	class multidigraph
	{
	public:
		class vertex; // forward-declare

		class edge
		{
		public:
			edge(vertex *from, vertex *to, E type, int id);
			edge(const edge &other) = delete;
			edge(edge &&other) = delete;
			edge &operator=(const edge &other) = delete;
			edge &operator=(edge &&other) = delete;

			friend class multidigraph;
			friend class vertex;

			bool operator==(const edge &other) const;
			bool operator!=(const edge &other) const;

			const vertex &from() const;
			const vertex &to() const;
			const E &type() const;

		private:
			int _id;
			vertex *_from;
			vertex *_to;
			E _type;
		};

		class vertex
		{
		public:
			vertex(V value, int id, multidigraph &graph);
			vertex(const vertex &other) = delete;
			vertex(vertex &&other) = delete;
			vertex &operator=(const vertex &other) = delete;
			vertex &operator=(vertex &&other) = delete;
			~vertex();

			friend class multidigraph;

			bool operator==(const vertex &other) const;
			bool operator!=(const vertex &other) const;

			const std::vector<std::reference_wrapper<edge>> &
			incoming() const;
			const std::vector<std::reference_wrapper<edge>> &
			outgoing() const;
			const V &value() const;
		private:
			multidigraph &_graph;
			std::vector<std::reference_wrapper<edge>> _edges_in;
			std::vector<std::reference_wrapper<edge>> _edges_out;
			int _id;
			V _value;
		};

		multidigraph();
		~multidigraph();

		edge &add_edge(vertex &from, vertex &to, E type);
		vertex &add_vertex(V value);

		template<typename U = V>
		typename std::enable_if<!is_unique_ptr<U>::value,
			std::vector<std::reference_wrapper<edge>>>::type
		find_edge(const U &from, const U &to, E type);
		template<typename U = V>
		typename std::enable_if<is_unique_ptr<U>::value,
			std::vector<std::reference_wrapper<edge>>>::type
		find_edge(const typename U::element_type &from,
		          const typename U::element_type &to, E type);

		template<typename U = V>
		typename std::enable_if<!is_unique_ptr<U>::value,
			std::vector<std::reference_wrapper<vertex>>>::type
		find_vertex(const U &value);
		template<typename U = V>
		typename std::enable_if<is_unique_ptr<U>::value,
			std::vector<std::reference_wrapper<vertex>>>::type
		find_vertex(const typename U::element_type &value);

		bool remove_edge(const edge &e);
		bool remove_vertex(const vertex &v);

		std::vector<std::reference_wrapper<vertex>> leaf_vertices();
		std::vector<std::reference_wrapper<vertex>> root_vertices();
		std::vector<std::reference_wrapper<vertex>> vertices();

	private:
		int _edge_counter;
		int _vertex_counter;
		std::list<edge> _edges;
		std::list<vertex> _vertices;
	};

#include "types/multidigraph.tpp"

} // piper

#endif //ZMQ_XML_THREAD_POC_MULTIDIGRAPH_HPP
