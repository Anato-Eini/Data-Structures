#ifndef DATA_STRUCTURES_ADJACENCYLIST_H
#define DATA_STRUCTURES_ADJACENCYLIST_H

#include "../General Graph/GraphAbstract.h"

namespace Graph {

    template<typename V, typename E>
    class AdjacencyList final: public GraphAbstract<V, E> {

        struct Vertex{
            V name;

            std::list<E> inEdges;

            std::list<E> outEdges;
        };

        std::list<Vertex> * list;

        size_t sizeEdge;

        GraphAbstract<V, E> &print(std::ostream &ostream) override;

    public:
        AdjacencyList();

        std::vector<V> * vertices() const override;

        std::vector<E> * edges() const override;

        std::vector<std::pair<V, V>> * endVertices(const E &edge) const override;

        std::vector<E> outgoingEdges(const V &vertex) const override;

        std::vector<E> incomingEdges(const V &vertex) const override;

        E getEdge(const V &vertex1, const V &vertex2) const override;

        std::vector<V> opposite(const V &vertex) const override;

        GraphAbstract<V, E> &addVertex(const V &vertex) override;

        GraphAbstract<V, E> &addEdge(const E &edge, const V &vertex1, const V &vertex2) override;

        GraphAbstract<V, E> &removeVertex(const V &vertex) override;

        GraphAbstract<V, E> &removeEdge(const E &edge) override;

        bool containEdge(const E &edge) const override;

        bool containVertex(const V &vertex) const override;

        size_t numVertices() const override;

        size_t numEdges() const override;

        size_t outDegree(const V &vertex) const override;

        size_t inDegree(const V &vertex) const override;

        ~AdjacencyList() override;
    };
}

#include "AdjacencyList.cpp"

#endif //DATA_STRUCTURES_ADJACENCYLIST_H
