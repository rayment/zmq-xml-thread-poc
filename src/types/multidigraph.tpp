/*
 * multidigraph.tpp
 *
 * Author       : Finn Rayment <finn@rayment.fr>
 * Date created : 08/07/2024
 */

template<typename V, typename E>
multidigraph<V, E>::edge::edge(multidigraph<V, E>::vertex *from,
                               multidigraph<V, E>::vertex *to,
                               E type,
                               int id) :
	_from(from), _to(to), _type(type), _id(id)
{}

template<typename V, typename E>
bool
multidigraph<V, E>::
edge::operator==(const multidigraph<V, E>::edge &other) const
{
	return _id == other._id;
}

template<typename V, typename E>
bool
multidigraph<V, E>::
edge::operator!=(const multidigraph<V, E>::edge &other) const
{
	return !(*this == other);
}

template<typename V, typename E>
const typename multidigraph<V, E>::vertex &
multidigraph<V, E>::edge::from() const
{
	return *_from;
}

template<typename V, typename E>
const typename multidigraph<V, E>::vertex &
multidigraph<V, E>::edge::to() const
{
	return *_to;
}

template<typename V, typename E>
const E &
multidigraph<V, E>::edge::type() const
{
	return _type;
}

template<typename V, typename E>
multidigraph<V, E>::vertex::vertex(V value,
                                   int id,
                                   multidigraph &graph) :
	_value(std::move(value)), _id(id), _graph(graph)
{}

template<typename V, typename E>
multidigraph<V, E>::vertex::~vertex()
{
	// delete all connections into the vertex as well as out from it
	for (auto &incoming_edge : _edges_in)
	{
		vertex &incoming = *incoming_edge.get()._from;
		auto it = std::find_if(incoming._edges_out.begin(),
		                       incoming._edges_out.end(),
			[this](const auto &ref)
			{
				return ref.get().to() == *this;
			}
		);
		if (it != incoming._edges_out.end())
			incoming._edges_out.erase(it);
	}
	for (auto &outgoing_edge : _edges_out)
	{
		vertex &outgoing = *outgoing_edge.get()._to;
		auto it = std::find_if(outgoing._edges_in.begin(),
		                       outgoing._edges_in.end(),
			[this](const auto &ref)
			{
				return ref.get().from() == *this;
			}
		);
		if (it != outgoing._edges_in.end())
			outgoing._edges_in.erase(it);
	}
	// now finally remove the real edge from the parent graph
	auto it = std::find_if(_graph._edges.begin(),
	                       _graph._edges.end(),
		[this](const auto &ref)
		{
			return ref.from() == *this ||
			       ref.to() == *this;
		}
	);
	if (it != _graph._edges.end())
		_graph._edges.erase(it);
}

template<typename V, typename E>
const std::vector<std::reference_wrapper<
	typename multidigraph<V, E>::edge>> &
multidigraph<V, E>::vertex::incoming() const
{
	return _edges_in;
}

template<typename V, typename E>
const std::vector<std::reference_wrapper<
	typename multidigraph<V, E>::edge>> &
multidigraph<V, E>::vertex::outgoing() const
{
	return _edges_out;
}

template<typename V, typename E>
const V &
multidigraph<V, E>::vertex::value() const
{
	return _value;
}

template<typename V, typename E>
bool
multidigraph<V, E>::
vertex::operator==(const multidigraph<V, E>::vertex &other) const
{
	return _id == other._id;
}

template<typename V, typename E>
bool
multidigraph<V, E>::
vertex::operator!=(const multidigraph<V, E>::vertex &other) const
{
	return !(*this == other);
}

template<typename V, typename E>
multidigraph<V, E>::multidigraph()
{
	_edge_counter = 0;
	_vertex_counter = 0;
}

template<typename V, typename E>
multidigraph<V, E>::~multidigraph()
{}

template<typename V, typename E>
typename multidigraph<V, E>::edge &
multidigraph<V, E>::add_edge(multidigraph::vertex &from,
                             multidigraph::vertex &to,
                             E type)
{
	auto &ref = _edges.emplace_back(&from, &to, type, _edge_counter++);
	from._edges_out.emplace_back(ref);
	to._edges_in.emplace_back(ref);
	return ref;
}

template<typename V, typename E>
typename multidigraph<V, E>::vertex &
multidigraph<V, E>::add_vertex(V value)
{
	auto &ref = _vertices.emplace_back(std::move(value), _vertex_counter++, *this);
	return ref;
}

template<typename V, typename E>
template<typename U>
typename std::enable_if<!is_unique_ptr<U>::value,
	std::vector<std::reference_wrapper<
		typename multidigraph<V, E>::edge>>>::type
multidigraph<V, E>::find_edge(const U &from,
                              const U &to,
                              E type)
{
	std::vector<std::reference_wrapper<edge>> result;
	for (const auto &vertex : _vertices)
	{
		if (!(vertex.value() == from))
			continue;
		for (auto &edge : vertex._edges_out)
		{
			if (edge.get().to().value() == to &&
			    edge.get().type() == type)
			{
				result.emplace_back(edge);
			}
		}
	}
	return result;
}

template<typename V, typename E>
template<typename U>
typename std::enable_if<is_unique_ptr<U>::value,
	std::vector<std::reference_wrapper<
		typename multidigraph<V, E>::edge>>>::type
multidigraph<V, E>::find_edge(const typename U::element_type &from,
                              const typename U::element_type &to,
                              E type)
{
	std::vector<std::reference_wrapper<edge>> result;
	for (const auto &vertex : _vertices)
	{
		if (!vertex.value() == from)
			continue;
		for (auto &edge : vertex._edges_out)
		{
			if (*edge.get().to().value() == to &&
			    *edge.get().type() == type)
			{
				result.emplace_back(edge);
			}
		}
	}
	return result;
}

template<typename V, typename E>
template<typename U>
typename std::enable_if<!is_unique_ptr<U>::value,
	std::vector<std::reference_wrapper<
		typename multidigraph<V, E>::vertex>>>::type
multidigraph<V, E>::find_vertex(const U &value)
{
	std::vector<std::reference_wrapper<vertex>> result;
	for (auto &vertex : _vertices)
	{
		if (vertex.value() == value)
			result.emplace_back(vertex);
	}
	return result;
}

template<typename V, typename E>
template<typename U>
typename std::enable_if<is_unique_ptr<U>::value,
	std::vector<std::reference_wrapper<
		typename multidigraph<V, E>::vertex>>>::type
multidigraph<V, E>::find_vertex(const typename U::element_type &value)
{
	std::vector<std::reference_wrapper<vertex>> result;
	for (auto &vertex : _vertices)
	{
		if (*vertex.value() == value)
			result.emplace_back(vertex);
	}
	return result;
}

template<typename V, typename E>
bool
multidigraph<V, E>::remove_edge(const edge &e)
{
	auto &edges_out = e._from->_edges_out;
	auto &edges_in = e._to->_edges_in;
	// delete the reference in the 'from' vertex
	auto it_out = std::find_if(edges_out.begin(),
	                           edges_out.end(),
		[&e](const auto &ref)
		{
			return ref.get() == e;
		}
	);
	if (it_out != edges_out.end())
		edges_out.erase(it_out);
	// delete the reference in the 'to' vertex
	auto it_in = std::find_if(edges_in.begin(),
	                          edges_out.end(),
		[&e](const auto &ref)
		{
			return ref.get() == e;
		}
	);
	if (it_in != edges_in.end())
		edges_in.erase(it_in);
	// now finally remove the real edge from the graph
	auto it = std::find_if(_edges.begin(),
	                       _edges.end(),
		[&e](const auto &ref)
		{
			return ref == e;
		}
	);
	if (it != _edges.end())
		_edges.erase(it);
	return false;
}

template<typename V, typename E>
bool
multidigraph<V, E>::remove_vertex(const vertex &v)
{
	auto it = std::find_if(_vertices.begin(), _vertices.end(),
		[&v](const auto &ref)
		{
			return ref == v;
		}
	);
	if (it != _vertices.end())
	{
		_vertices.erase(it);
		return true;
	}
	return false;
}

template<typename V, typename E>
std::vector<std::reference_wrapper<
	typename multidigraph<V, E>::vertex>>
multidigraph<V, E>::root_vertices()
{
	std::vector<std::reference_wrapper<vertex>> roots;
	for (auto &vertex : _vertices)
	{
		bool has_incoming_edge = false;
		for (const auto &edge : vertex._edges_in)
		{
			// incoming edges only apply if the edge is NOT self-referencing
			if (edge.get().from() != edge.get().to())
			{
				has_incoming_edge = true;
				break;
			}
		}
		if (!has_incoming_edge)
			roots.emplace_back(vertex);
	}
	return roots;
}
