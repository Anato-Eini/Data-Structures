#ifndef GRAPHS_EDGELIST_CPP
#define GRAPHS_EDGELIST_CPP
#include "EdgeList.h"

namespace Graph {

    template <typename V, typename E>
    EdgeList<V, E>::EdgeList() : _edges(new std::list<E>), _vertices(new std::list<V>) {}

    template<typename V, typename E>
    std::vector<V>* EdgeList<V, E>::vertices() const {
    	auto * vertices = new std::vector<V>;

    	std::transform(_vertices->begin(), _vertices->end(), std::back_inserter(*vertices),
    		[](const V & vertex) -> V {return vertex;});

        return vertices;
    }

    template<typename V, typename E>
    std::vector<E>* EdgeList<V, E>::edges() const {
    	auto * edges = new std::vector<E>;

    	std::transform(_edges->begin(), _edges->end(), std::back_inserter(*edges),
    		[](const E & edge) -> E {return edge;});

        return _edges;
    }

    template<typename V, typename E>
    std::vector<std::pair<V, V>>* EdgeList<V, E>::endVertices(const E &edge) {
    	auto* vertices = new std::vector<std::pair<V, V>>;

    	std::for_each(_edges->begin(), _edges->end(), [& vertices, & edge](const E & e) -> void
    	{
    		if(edge == e)
				vertices->emplace_back({e.vertex1, e.vertex2});
    	});

        return vertices;
    }

    template<typename V, typename E>
    std::vector<E>* EdgeList<V, E>::outgoingEdges(const V &vertex) {
        auto * outgoingEdges = new std::vector<E>();

    	std::for_each(_edges->begin(), _edges->end(), [&outgoingEdges, &vertex] (const E & e) -> void
    	{
    		if(e.vertex1 == vertex)
				outgoingEdges->emplace_back(e);
    	});

        return outgoingEdges;
    }

    template<typename V, typename E>
    std::vector<E>* EdgeList<V, E>::incomingEdges(const V &vertex) {
    	auto * incomingEdges = new std::vector<E>();

    	for (const E & edge: _edges)
    		if(edge.vertex2 == vertex)
    			incomingEdges->push_back(edge.edgeName);

    	std::for_each(_edges->begin(), _edges->end(), [& incomingEdges, &vertex](const E & e) -> void
    	{
    		if(e.vertex2 == vertex)
    			incomingEdges->emplace_back(e);
    	});

        return incomingEdges;
    }

    template<typename V, typename E>
    E EdgeList<V, E>::getEdge(const V &vertex1, const V &vertex2) {
		for (const E & edges: _edges)
			if(edges.vertex1 == vertex1 && edges.vertex2 == vertex2)
				return edges.edgeName;

        return {};
    }

    template <typename V, typename E>
    std::pmr::set<E>* EdgeList<V, E>::unique_edge()
    {
        auto* unique_edges = new std::set<E>();

    	std::for_each(_edges->begin(), _edges->end(), [&unique_edges](const E & edges) -> void
    			{ unique_edges->insert(edges.edgeName); });

        return unique_edges;
    }

    template<typename V, typename E>
    std::vector<V>* EdgeList<V, E>::opposite(const V &vertex) {
        auto* oppositeVertices = new std::vector<V>();

    	std::for_each(_edges->begin(), _edges->end(), [& oppositeVertices, & vertex](const E & edge) -> void
    	{
    		if(edge.vertex1 == vertex)
    			oppositeVertices->emplace_back(edge.edgeName);
    	});

        return oppositeVertices;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::addVertex(const V &vertex) {
        if (_vertices->contains(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");

		_vertices->emplace_back(vertex);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::add_directed_Edge(const E &edge, const V &vertex1, const V &vertex2) {
        if(!_vertices->contains(vertex1) || !_vertices->contains(vertex2))
            throw std::logic_error("vertex doesn't exists\n");

        _edges->push_back({edge, vertex1, vertex2});

        return *this;
    }

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::add_bidirected_Edge(const E &edge, const V &vertex1, const V &vertex2)
	{
    	if(!_vertices->contains(vertex1) || !_vertices->contains(vertex2))
    		throw std::logic_error("vertex doesn't exists\n");

    	_edges->push_back({edge, vertex1, vertex2});
    	_edges->push_back({edge, vertex2, vertex1});

    	return *this;
	}

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::removeVertex(const V &vertex) {
    	typename std::list<E>::iterator iterator = std::find(_vertices->begin(), _vertices->end(), vertex);

    	if(iterator == _vertices->end())
    		return *this;

		_vertices->erase(iterator);

    	_edges->remove_if([&vertex] (const E & edge) -> bool
    	{  return edge.vertex1 == vertex || edge.vertex2 == vertex; });

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::removeEdge(const E &edge) {

    	_edges->remove_if([& edge] (const E & _edge) -> bool { return _edge.edgeName == edge;});

        return *this;
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::numVertices() {
        return _vertices->size();
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::numEdges() {
        return _edges->size();
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::outDegree(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");

    	std::vector<E> * outEdges = outgoingEdges(vertex);
		const size_t outDegree = outEdges->size();
    	delete outEdges;
        return outDegree;
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::inDegree(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");

    	std::vector<E> * inEdges = incomingEdges(vertex);
    	const size_t inDegree = inEdges->size();
    	delete inEdges;
        return inDegree;
    }

    template<typename V, typename E>
    bool EdgeList<V, E>::containEdge(const E &edge) const {
        return std::ranges::find(_edges, edge) != _edges->end();
    }

    template<typename V, typename E>
    bool EdgeList<V, E>::containVertex(const V &vertex) const {
        return std::ranges::find(_vertices, vertex) != _vertices->end();
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::print(std::ostream &ostream) {
        ostream << "Vertices:";
        for (const V &s: _vertices)
            ostream << " " << s;
            ostream << "\nEdges:\n";
        for (const E & edge: _edges)
            ostream << "Name: " << edge.edgeName << " <" << edge.vertex1 << ", " << edge.vertex2 << ">\n";

        return *this;
    }
}

#endif