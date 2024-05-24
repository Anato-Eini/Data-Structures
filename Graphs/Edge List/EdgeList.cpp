#ifndef GRAPHS_EDGELIST_CPP
#define GRAPHS_EDGELIST_CPP
#include "EdgeList.h"

namespace Graph {

    template<typename V, typename E>
    std::vector<V> EdgeList<V, E>::vertices() const {
        std::vector<V> vertices;
        std::transform(Vertices.begin(), Vertices.end(), std::back_inserter(vertices),
                       [](const V &s) -> V {
                           return s;
                       });
        return vertices;
    }

    template<typename V, typename E>
    std::vector<E> EdgeList<V, E>::edges() const {
        std::vector<E> edges;
        std::transform(Edges.begin(), Edges.end(), std::back_inserter(edges),
                       [](const std::pair<const E, std::pair<V, V>> &edge) -> E {
                           return edge.first;
                       });
        return edges;
    }

    template<typename V, typename E>
    std::pair<V, V> EdgeList<V, E>::endVertices(const E &edge) {
        auto it = Edges.find(edge);
        if (it == Edges.end())
            throw std::logic_error(edge + " edge doesn't exist\n");
        return it->second;
    }

    template<typename V, typename E>
    std::vector<E> EdgeList<V, E>::outgoingEdges(const V &vertex) {
        if (!Vertices.contains(vertex))
            throw std::logic_error(vertex + " vertex doesn't exists\n");
        std::vector<E> outgoingEdges;
        for (const std::pair<const E, std::pair<V, V>> &pair: Edges)
            if (pair.second.first == vertex || pair.second.second == vertex)
                outgoingEdges.emplace_back(pair.first);
        return outgoingEdges;
    }

    template<typename V, typename E>
    std::vector<E> EdgeList<V, E>::incomingEdges(const V &vertex) {
        return outgoingEdges(vertex);
    }

    template<typename V, typename E>
    E EdgeList<V, E>::getEdge(const V &vertex1, const V &vertex2) {
        if (!containVertex(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exist\n");
        else if (!containVertex(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exist\n");
        for (const std::pair<const E, std::pair<V, V>> &pair: Edges)
            if ((pair.second.first == vertex1 || pair.second.first == vertex2) &&
                (pair.second.second == vertex1 || pair.second.second == vertex2))
                return pair.first;
        return {};
    }

    template<typename V, typename E>
    std::vector<V> EdgeList<V, E>::opposite(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        std::vector<V> oppositeVertices;
        for (const std::pair<const E, std::pair<V, V>> &pair: Edges) {
            if (pair.second.first == vertex)
                oppositeVertices.emplace_back(pair.second.second);
            else if (pair.second.second == vertex)
                oppositeVertices.emplace_back(pair.second.first);
        }
        return oppositeVertices;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::addVertex(const V &vertex) {
        if (Vertices.contains(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");
        Vertices.insert(vertex);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::addEdge(const E &edge, const V &vertex1, const V &vertex2) {
        if (Edges.contains(edge))
            throw std::logic_error(edge + " edge already exists\n");
        else if (!Vertices.contains(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exist\n");
        else if (!Vertices.contains(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exist\n");
        else
            Edges.insert({edge, {vertex1, vertex2}});

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::removeVertex(const V &vertex) {
        auto iterator = Vertices.find(vertex);
        if (iterator != Vertices.end()) {
            Vertices.erase(*iterator);
            std::vector<E> to_be_deleted;
            for (std::pair<const E, std::pair<V, V>> &pair: Edges)
                if (pair.second.first == vertex || pair.second.second == vertex)
                    to_be_deleted.emplace_back(pair.first);
            for (const E &edge: to_be_deleted)
                Edges.erase(edge);
        } else throw std::logic_error(vertex + " vertex doesn't exist\n");

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &EdgeList<V, E>::removeEdge(const E &edge) {
        auto iterator = Edges.find(edge);
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