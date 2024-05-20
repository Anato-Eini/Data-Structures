#ifndef DATA_STRUCTURES_EDGELIST_H
#define DATA_STRUCTURES_EDGELIST_H

#include "../General Graph/Graph.h"

template <typename V, typename E>
class EdgeList: public Graph<V, E>{
    std::unordered_set<V> Vertices;
    //unordered_map<Edge, <vertex1, vertex2>>
    std::unordered_map<E, std::pair<V, V>> Edges;

    void print(std::ostream &ostream) override;
public:
    std::vector<V> vertices() const override;

    std::vector<E> edges() const override;

    std::pair<V, V> endVertices(const E &edge) override;

    std::vector<E> outgoingEdges(const V &vertex) override;

    std::vector<E> incomingEdges(const V &vertex) override;

    E getEdge(const V &vertex1, const V &vertex2) override;

    std::vector<V> opposite(const V &vertex) override;

    void addVertex(const V &vertex) override;

    void addEdge(const E &edge, const V &vertex1, const V &vertex2) override;

    void removeVertex(const V &vertex) override;

    void removeEdge(const E &edge) override;

    bool containEdge(const E &edge) const override;

    bool containVertex(const V &vertex) const override;

    int numVertices() override;

    int numEdges() override;

    int outDegree(const V &vertex) override;

    int inDegree(const V &vertex) override;
};

#endif //DATA_STRUCTURES_EDGELIST_H
