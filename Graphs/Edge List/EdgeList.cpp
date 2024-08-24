#ifndef GRAPHS_EDGELIST_CPP
#define GRAPHS_EDGELIST_CPP
#include "EdgeList.h"

namespace Graph {

    template <typename V, typename E>
    EdgeList<V, E>::EdgeList() : _edges(new std::list<E>), _vertices(new std::list<V>) {}

    template<typename V, typename E>
    std::vector<V>* EdgeList<V, E>::vertices() const {
        return _vertices;
    }

    template<typename V, typename E>
    std::vector<E>* EdgeList<V, E>::edges() const {
        return _edges;
    }

    template<typename V, typename E>
    std::vector<std::pair<V, V>>* EdgeList<V, E>::endVertices(const E &edge) {
    	auto* vertices = new std::vector<std::pair<V, V>>;
		for (const E & edges: _edges)
			if(edge == edges.edgeName)
				vertices->push_back({edges.vertex1, edges.vertex2});
        return vertices;
    }

    template<typename V, typename E>
    std::vector<E>* EdgeList<V, E>::outgoingEdges(const V &vertex) {
        auto * outgoingEdges = new std::vector<E>();

		for	(const E & edges: _edges)
			if(edges.vertex1 == vertex)
				outgoingEdges->push_back(edges.edgeName);

        return outgoingEdges;
    }

    template<typename V, typename E>
    std::vector<E>* EdgeList<V, E>::incomingEdges(const V &vertex) {
    	auto * incomingEdges = new std::vector<E>();

    	for (const E & edge: _edges)
    		if(edge.vertex2 == vertex)
    			incomingEdges->push_back(edge.edgeName);

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
        std::set<E> unique_edges = new std::set<E>();
    	std::for_each(_edges.begin(), _edges.end(), [&unique_edges](const E & edges) -> void
    			{ unique_edges.insert(edges.edgeName); });

        return unique_edges;
    }


    template<typename V, typename E>
    std::vector<V>* EdgeList<V, E>::opposite(const V &vertex) {
        auto* oppositeVertices = new std::vector<V>();

    	std::for_each(_edges.begin(), _edges.end(), [&oppositeVertices, & vertex](const E & edge) -> void
    	{
    		if(edge.vertex1 == vertex)
    			oppositeVertices->push_back(edge.edgeName);
    	});

        return oppositeVertices;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::addVertex(const V &vertex) {
        if (_vertices.contains(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");

		_vertices->push_back(vertex);
        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::add_directed_Edge(const E &edge, const V &vertex1, const V &vertex2) {
        if(!_vertices.contains(vertex1) || !_vertices.contains(vertex2))
            throw std::logic_error("vertex doesn't exists\n");

        _edges->push_back({edge, vertex1, vertex2});

        return *this;
    }

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::add_bidirected_Edge(const E &edge, const V &vertex1, const V &vertex2)
	{
    	if(!_vertices.contains(vertex1) || !_vertices.contains(vertex2))
    		throw std::logic_error("vertex doesn't exists\n");

    	_edges->push_back({edge, vertex1, vertex2});
    	_edges->push_back({edge, vertex2, vertex1});

    	return *this;
	}

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::removeVertex(const V &vertex) {
		_vertices->erase(std::find(_vertices.begin(), _vertices.end(), vertex));

    	std::vector<typename std::list<E>::iterator> iterators;

    	for (typename std::list<E>::iterator it = _edges.begin(); it != _edges.end(); ++it)
    		if(it->vertex1 == vertex || it->vertex2 == vertex)
    			iterators.push_back(it);

    	std::for_each(iterators.begin(), iterators.end(), [this]
    		(const typename std::vector<E>::iterator & it) -> void
    	{ _edges->erase(std::find(_edges.begin(), _edges.end(), it)); });

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::removeEdge(const E &edge) {
        auto iterator = _vertices.find(edge);
    	_vertices.erase(_vertices.find(e))
        if (iterator != Edges.end())
            Edges.erase(iterator);
        else
            throw std::logic_error(edge + " edge doesn't exist\n");

        return *this;
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::numVertices() {
        return Vertices.size();
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::numEdges() {
        return Edges.size();
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::outDegree(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        auto iterator = Vertices.find(vertex);
        if (iterator != Vertices.end()) {
            size_t numOutDegree = 0;
            for (const std::pair<const E, std::pair<V, V> > &pair: Edges)
                if (pair.second.first == vertex || pair.second.second == vertex)
                    numOutDegree++;
            return numOutDegree;
        }
        return -1;
    }

    template<typename V, typename E>
    size_t EdgeList<V, E>::inDegree(const V &vertex) {
        return outDegree(vertex);
    }

    template<typename V, typename E>
    bool EdgeList<V, E>::containEdge(const E &edge) const {
        return Edges.contains(edge);
    }

    template<typename V, typename E>
    bool EdgeList<V, E>::containVertex(const V &vertex) const {
        return Vertices.contains(vertex);
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::print(std::ostream &ostream) {
        ostream << "Vertices:";
        for (const V &s: Vertices)
            ostream << " " << s;
        ostream << "\nEdges:\n";
        for (const std::pair<const E, std::pair<V, V>> &pair: Edges)
            ostream << "Name: " << pair.first << " <" << pair.second.first << ", " << pair.second.second << ">\n";

        return *this;
    }
}

#endif