#ifndef DATA_STRUCTURES_ADJACENCYMATRIX_H
#define DATA_STRUCTURES_ADJACENCYMATRIX_H

#include "../General Graph/Graph.h"

template<typename V, typename E>
class AdjacencyMatrix : public Graph<V, E>{
    /*
     * <rowVertex, <colVertex, edge>>
     * The reason this is implemented this way it to get a particular edges by matrix[vertex1][vertex2] based on
     * the visualization given that that particular edge really exists
    */
    std::unordered_map<V, std::unordered_map<V, E>> matrix;

    Graph<V, E>& print(std::ostream &ostream) override;
public:
    std::vector<V> vertices() const override;

    std::vector<E> edges() const override;

    std::pair<V, V> endVertices(const E &edge) override;

    std::vector<E> outgoingEdges(const V &vertex) override;

    std::vector<E> incomingEdges(const V &vertex) override;

    E getEdge(const V &vertex1, const V &vertex2) override;

    std::vector<V> opposite(const V &vertex) override;

    Graph<V, E>& addVertex(const V &vertex) override;

    Graph<V, E>& addEdge(const E &edge, const V &vertex1, const V &vertex2) override;

    Graph<V, E>& removeVertex(const V &vertex) override;

    Graph<V, E>& removeEdge(const E &edge) override;

    bool containEdge(const E &edge) const override;

    bool containVertex(const V &vertex) const override;

    int numVertices() override;

    int numEdges() override;

    int outDegree(const V &vertex) override;

    int inDegree(const V &vertex) override;
};


#endif //DATA_STRUCTURES_ADJACENCYMATRIX_H
