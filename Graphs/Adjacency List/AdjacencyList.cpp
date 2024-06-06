#ifndef DATA_STRUCTURES_ADJACENCYLIST_CPP
#define DATA_STRUCTURES_ADJACENCYLIST_CPP

#include "AdjacencyList.h"

namespace Graph {

    template<typename V, typename E>
    std::vector<V> AdjacencyList<V, E>::vertices() const {
        std::vector<V> vertices;
        for (const std::pair<const V, std::unordered_set<E>> &pair: list)
            vertices.emplace_back(pair.first);
        return vertices;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyList<V, E>::edges() const {
        std::vector<E> edges;
        for (const std::pair<const V, std::unordered_set<E>> &pair: list)
            for (const E &s: pair.second) {
                if (std::any_of(edges.begin(), edges.end(), [&s](const E &edge) -> bool {
                    return s == edge;
                }))
                    continue;
                edges.emplace_back(s);
            }
        return edges;
    }

    template<typename V, typename E>
    std::pair<V, V> AdjacencyList<V, E>::endVertices(const E &edge) {
        if (!containEdge(edge))
            throw std::logic_error(edge + " edge doesn't exist\n");

        std::pair<V, V> pairVertices({}, {});
        for (const std::pair<const V, std::unordered_set<E>> &pair: list)
            if (pair.second.contains(edge)) {
                if (pairVertices.first == (V) {})
                    pairVertices.first = pair.first;
                else
                    pairVertices.second = pair.first;
            }
        return pairVertices;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyList<V, E>::outgoingEdges(const V &vertex) {
        std::vector<E> outgoingEdges;
        if (list.contains(vertex))
            for (const E &edges: list[vertex])
                outgoingEdges.emplace_back(edges);
        return outgoingEdges;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyList<V, E>::incomingEdges(const V &vertex) {
        return outgoingEdges(vertex);
    }

    template<typename V, typename E>
    E AdjacencyList<V, E>::getEdge(const V &vertex1, const V &vertex2) {
        if (!containVertex(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exist\n");
        else if (!containVertex(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exist\n");

        if (list[vertex1].size() > list[vertex2].size()) {
            for (const E &edge: list[vertex2])
                if (list[vertex1].contains(edge))
                    return edge;
        } else {
            for (const E &edge: list[vertex1])
                if (list[vertex2].contains(edge))
                    return edge;
        }
        return {};
    }

    template<typename V, typename E>
    std::vector<V> AdjacencyList<V, E>::opposite(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        std::vector<V> oppositeVertices;
        for (const std::pair<const V, std::unordered_set<E>> &pair: list)
            if (pair.first != vertex)
                for (const E &edge: list[vertex])
                    if (pair.second.contains(edge)) {
                        oppositeVertices.emplace_back(pair.first);
                        break;
                    }
        return oppositeVertices;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::addVertex(const V &vertex) {
        if (list.contains(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");
        list.insert({vertex, {}});

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::addEdge(const E &edge, const V &vertex1, const V &vertex2) {
        if (!list.contains(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exists\n");

        list[vertex1].insert(edge);
        list[vertex2].insert(edge);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::removeVertex(const V &vertex) {
        if (!list.contains(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");

        list.erase(vertex);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::removeEdge(const E &edge) {
        if (!containEdge(edge))
            throw std::logic_error(edge + " edge doesn't exist\n");
        for (std::pair<const V, std::unordered_set<E>> &p: list)
            if (p.second.contains(edge))
                p.second.erase(edge);

        return *this;
    }

    template<typename V, typename E>
    bool AdjacencyList<V, E>::containEdge(const E &edge) const {
        return std::ranges::any_of(list, [&edge]
                (const std::pair<const V, std::unordered_set<E>> &p) -> bool {
            return p.second.contains(edge);
        });
    }

    template<typename V, typename E>
    bool AdjacencyList<V, E>::containVertex(const V &vertex) const {
        return list.contains(vertex);
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::numVertices() {
        return list.size();
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::numEdges() {
        size_t numEdges = 0;
        for (const std::pair<const V, std::unordered_set<E>> &p: list)
            numEdges += p.second.size();
        return numEdges;
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::outDegree(const V &vertex) {
        if (!list.contains(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist");
        return list[vertex].size();
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::inDegree(const V &vertex) {
        return outDegree(vertex);
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::print(std::ostream &ostream) {
        bool isFirst = true;
        for (const std::pair<const V, std::unordered_set<E>> &p: list) {
            ostream << "Vertex " << p.first << "\t";
            for (const E &edge: p.second) {
                if (isFirst) {
                    ostream << " " << edge;
                    isFirst = false;
                } else
                    ostream << " -> " << edge;
            }
            isFirst = true;
            ostream << '\n';
        }
        return *this;
    }
}

#endif