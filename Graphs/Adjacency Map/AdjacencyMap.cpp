#ifndef DATA_STRUCTURES_ADJACENCYMAP_CPP
#define DATA_STRUCTURES_ADJACENCYMAP_CPP

#include "AdjacencyMap.h"

namespace Graph {

    template<typename V, typename E>
    std::vector<V> AdjacencyMap<V, E>::vertices() const {
        std::vector<V> vertices;
        for (const std::pair<const V, std::unordered_map<E, V>> &p: Vertices)
            vertices.emplace_back(p.first);
        return vertices;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyMap<V, E>::edges() const {
        std::vector<E> edges;
        for (const std::pair<const V, std::unordered_map<E, V>> &p: Vertices) {
            auto it =
                    std::find_if_not(p.second.begin(), p.second.end(),
                                     [&edges](const std::pair<const E, V> &edgeVertices) -> bool {
                                         return std::any_of(edges.begin(), edges.end(),
                                                            [edgeVertices](const E &s) -> bool {
                                                                return edgeVertices.first == s;
                                                            });
                                     });
            if (it != p.second.end())
                edges.emplace_back(it->first);
        }
        return edges;
    }

    template<typename V, typename E>
    std::pair<V, V> AdjacencyMap<V, E>::endVertices(const E &edge) {
        if (!containEdge(edge))
            throw std::logic_error(edge + " edge doesn't exist\n");
        std::pair<V, V> pairOfVertices{{},
                                       {}};
        for (const std::pair<const V, std::unordered_map<E, V>> &vertexEdge: Vertices)
            if (vertexEdge.second.contains(edge)) {
                if (pairOfVertices.first.empty())
                    pairOfVertices.first = vertexEdge.first;
                else
                    pairOfVertices.second = vertexEdge.first;
            }
        return pairOfVertices;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyMap<V, E>::outgoingEdges(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        std::vector<E> edges;
        std::transform(Vertices[vertex].begin(), Vertices[vertex].end(), std::back_inserter(edges),
                       [](const std::pair<const E, V> &edge) -> E {
                           return edge.first;
                       });
        return edges;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyMap<V, E>::incomingEdges(const V &vertex) {
        return outgoingEdges(vertex);
    }

    template<typename V, typename E>
    E AdjacencyMap<V, E>::getEdge(const V &vertex1, const V &vertex2) {
        if (!containVertex(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exist\n");
        else if (!containVertex(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exist\n");
        V large = Vertices[vertex1].size() > Vertices[vertex2].size() ? vertex1 : vertex2
        , small = Vertices[vertex1].size() > Vertices[vertex2].size() ? vertex2 : vertex1;
        auto it =
                std::find_if(Vertices[small].begin(), Vertices[small].end(),
                             [&large](const std::pair<const E, V> &edgeVertex) -> bool {
                                 return edgeVertex.second == large;
                             });
        if (it != Vertices[small].end())
            return it->first;
        return {};
    }

    template<typename V, typename E>
    std::vector<V> AdjacencyMap<V, E>::opposite(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exists\n");
        std::vector<V> vertices;
        std::transform(Vertices[vertex].begin(), Vertices[vertex].end(), std::back_inserter(vertices),
                       [](const std::pair<const E, V> &edges) -> V {
                           return edges.second;
                       });
        return vertices;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMap<V, E>::addVertex(const V &vertex) {
        if (containVertex(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");
        Vertices.insert({vertex, {}});

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMap<V, E>::addEdge(const E &edge, const V &vertex1, const V &vertex2) {
        if (containEdge(edge))
            throw std::logic_error(edge + " edge already exists\n");
        else if (!containVertex(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exists\n");
        else if (!containVertex(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exists\n");
        Vertices[vertex1].insert({edge, vertex2});
        Vertices[vertex2].insert({edge, vertex1});

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMap<V, E>::removeVertex(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exists\n");
        Vertices.erase(vertex);
        for (std::pair<const V, std::unordered_map<E, V>> &vertex1: Vertices) {
            auto it = std::ranges::find_if(
                    vertex1.second, [&vertex](const std::pair<const E, V> &edgeVertex) -> bool {
                        return edgeVertex.second == vertex;
                    });
            if (it != vertex1.second.end())
                vertex1.second.erase(it->first);
        }

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMap<V, E>::removeEdge(const E &edge) {
        if (!containEdge(edge))
            throw std::logic_error(edge + " edge doesn't exists\n");
        for (std::pair<const V, std::unordered_map<E, V>> &edges: Vertices)
            edges.second.erase(edge);

        return *this;
    }

    template<typename V, typename E>
    bool AdjacencyMap<V, E>::containEdge(const E &edge) const {
        return std::ranges::any_of(Vertices, [&edge]
                (const std::pair<V, std::unordered_map<E, V>> &pair) -> bool {
            return pair.second.contains(edge);
        });
    }

    template<typename V, typename E>
    bool AdjacencyMap<V, E>::containVertex(const V &vertex) const {
        return Vertices.contains(vertex);
    }

    template<typename V, typename E>
    size_t AdjacencyMap<V, E>::numVertices() {
        return Vertices.size();
    }

    template<typename V, typename E>
    size_t AdjacencyMap<V, E>::numEdges() {
        return edges().size();
    }

    template<typename V, typename E>
    size_t AdjacencyMap<V, E>::outDegree(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        return Vertices[vertex].size();
    }

    template<typename V, typename E>
    size_t AdjacencyMap<V, E>::inDegree(const V &vertex) {
        return outDegree(vertex);
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMap<V, E>::print(std::ostream &ostream) {
        ostream << "Size: " << Vertices.size() << '\n';
        for (const std::pair<const V, std::unordered_map<E, V>> &pair: Vertices) {
            ostream << "Vertex " << pair.first << "\nEdges:\n";
            for (const std::pair<const E, V> &edgeVertex: pair.second)
                ostream << edgeVertex.first << " -> " << edgeVertex.second << '\n';
        }

        return *this;
    }
}

#endif