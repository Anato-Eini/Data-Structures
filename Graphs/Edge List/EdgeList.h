#ifndef DATA_STRUCTURES_EDGELIST_H
#define DATA_STRUCTURES_EDGELIST_H

#include "../General Graph/GraphAbstract.h"

namespace Graph {

    template<typename V, typename E>
    class EdgeList final : public GraphAbstract<V, E>
	{

    	struct Edge
    	{
    		E edgeName;

    		///From vertex1 to vertex2
    		V vertex1, vertex2;
    	};

        std::list<Edge>* _edges;

        std::list<V>* _vertices;

        GraphAbstract<V, E> &print(std::ostream &ostream) override;

    public:
        EdgeList();

        std::vector<V>* vertices() const override;

        std::vector<E>* edges() const override;

        std::vector<std::pair<V, V>>* endVertices(const E &edge) const override;

        std::vector<E>* outgoingEdges(const V &vertex) const override;

        std::vector<E>* incomingEdges(const V &vertex) const override;

        E getEdge(const V &vertex1, const V &vertex2) const override;

        std::vector<V>* opposite(const V &vertex) const override;

        GraphAbstract<V, E> &addVertex(const V &vertex) override;

        GraphAbstract<V, E> &add_directed_Edge(const E &edge, const V &vertex1, const V &vertex2) override;

    	GraphAbstract<V, E> & add_bidirected_Edge(const E &edge, const V &vertex1, const V &vertex2) override;

        GraphAbstract<V, E> &removeVertex(const V &vertex) override;

        std::vector<E>* unique_edge() const override;

        GraphAbstract<V, E> &removeEdge(const E &edge) override;

        bool containEdge(const E &edge) const override;

        bool containVertex(const V &vertex) const override;

        size_t numVertices() const override;

        size_t numEdges() const override;

        size_t outDegree(const V &vertex) const override;

        size_t inDegree(const V &vertex) const override;

        ~EdgeList() override;
    };
}

#include "EdgeList.cpp"

#endif //DATA_STRUCTURES_EDGELIST_H
