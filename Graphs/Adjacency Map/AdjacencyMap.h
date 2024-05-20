#ifndef DATA_STRUCTURES_ADJACENCYMAP_H
#define DATA_STRUCTURES_ADJACENCYMAP_H

#include "../General Graph/Graph.h"

template <typename V, typename E>
class AdjacencyMap : public Graph<V, E>{
    //<vertex, <edge, vertex>>
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> Vertices;

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


#endif //DATA_STRUCTURES_ADJACENCYMAP_H
