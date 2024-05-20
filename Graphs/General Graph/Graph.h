#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

template <typename V, typename E>
class Graph{
    virtual Graph& print(std::ostream&) = 0;

public:
    virtual std::vector<V> vertices() const = 0;

    virtual std::vector<E> edges() const = 0;

    ///Returns a pair of empty strings if none
    virtual std::pair<V, V> endVertices(const E &edge) = 0;

    virtual std::vector<E> outgoingEdges(const V &vertex) = 0;

    virtual std::vector<E> incomingEdges(const V &vertex) = 0;

    virtual E getEdge(const V &vertex1, const V &vertex2) = 0;

    virtual std::vector<V> opposite(const V &vertex) = 0;

    ///Must be unique
    virtual Graph& addVertex(const V &vertex) = 0;

    ///Must be unique

    virtual Graph& addEdge(const E &edge, const V &vertex1, const V &vertex2) = 0;

    virtual Graph& removeVertex(const V &vertex) = 0;

    virtual Graph& removeEdge(const E &edge) = 0;

    virtual bool containEdge(const E &edge) const = 0;

    virtual bool containVertex(const V &vertex) const = 0;

    virtual int numVertices() = 0;

    virtual int numEdges() = 0;

    virtual int outDegree(const V &vertex) = 0;

    virtual int inDegree(const V &vertex) = 0;

    friend std::ostream& operator<<(std::ostream&, Graph<V, E>* graph);

    friend std::ostream& operator<<(std::ostream&, Graph<V, E>& graph);

    virtual ~Graph() = default;
};

template <typename V, typename E>
std::ostream& operator<<(std::ostream& os, Graph<V, E>* graph);

template <typename V, typename E>
std::ostream& operator<<(std::ostream& os, Graph<V, E>& graph);

#endif //DATA_STRUCTURES_GRAPH_H
