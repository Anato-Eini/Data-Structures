#ifndef DATA_STRUCTURES_ADJACENCYMATRIX_CPP
#define DATA_STRUCTURES_ADJACENCYMATRIX_CPP
#include "AdjacencyMatrix.h"

namespace Graph {

    template<typename V, typename E>
    std::vector<V> AdjacencyMatrix<V, E>::vertices() const {
        std::vector<V> arrOfVertices;
        std::transform(matrix.begin(), matrix.end(), std::back_inserter(arrOfVertices),
                       [](const std::pair<const V, std::unordered_map<V, E>> &pair)
                               -> V { return pair.first; });
        return arrOfVertices;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyMatrix<V, E>::edges() const {
        std::unordered_set<E> edgeSet; // For faster look-up
        std::vector<E> arrOfEdges;
        for (const std::pair<const V, std::unordered_map<V, E>> &row: matrix)
            for (const std::pair<const V, E> &column: row.second)
                if (!edgeSet.contains(column.second))
                    edgeSet.insert(column.second);
        edgeSet.erase((E){});
        std::transform(edgeSet.begin(), edgeSet.end(), std::back_inserter(arrOfEdges),
                       [](const E &e) -> E { return e; });
        return arrOfEdges;
    }

    template<typename V, typename E>
    std::pair<V, V> AdjacencyMatrix<V, E>::endVertices(const E &edge) {
        for (const std::pair<const V, std::unordered_map<V, E>> &row: matrix) {
            auto it = std::find_if(row.second.begin(), row.second.end(),
                                   [&edge](const std::pair<const V, E> &cell) -> bool {
                                       return cell.second == edge;
                                   });
            if (it != row.second.end())
                return {row.first, it->first};
        }
        throw std::logic_error(edge + " edge doesn't exist\n");
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyMatrix<V, E>::outgoingEdges(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        std::vector<E> edges;
        for (const std::pair<const V, E> &cell: matrix[vertex])
            if (cell.second != (E){})
                edges.push_back(cell.second);
        return edges;
    }

    template<typename V, typename E>
    std::vector<E> AdjacencyMatrix<V, E>::incomingEdges(const V &vertex) {
        return outgoingEdges(vertex);
    }

    template<typename V, typename E>
    E AdjacencyMatrix<V, E>::getEdge(const V &vertex1, const V &vertex2) {
        if (!containVertex(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exist\n");
        else if (!containVertex(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exist\n");
        return matrix[vertex1][vertex2];
    }

    template<typename V, typename E>
    std::vector<V> AdjacencyMatrix<V, E>::opposite(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        std::vector<V> vertices;
        for (const std::pair<const V, E> &row: matrix[vertex])
            if (row.second != (E) {})
                vertices.push_back(row.first);
        return vertices;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMatrix<V, E>::addVertex(const V &vertex) {
        if (containVertex(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");
        matrix[vertex] = {};
        for (std::pair<const V, std::unordered_map<V, E>> &row: matrix)
            matrix[vertex][row.first] = row.second[vertex] = {};

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMatrix<V, E>::addEdge(const E &edge, const V &vertex1, const V &vertex2) {
        matrix[vertex2][vertex1] = matrix[vertex1][vertex2] = edge;

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMatrix<V, E>::removeVertex(const V &vertex) {
        if (!containVertex(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");
        matrix.erase(vertex);
        for (std::pair<const V, std::unordered_map<V, E>> &row: matrix)
            row.second.erase(vertex);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMatrix<V, E>::removeEdge(const E &edge) {
        for (std::pair<const V, std::unordered_map<V, E>> &row: matrix)
            for (std::pair<const V, E> &cell: row.second)
                if (cell.second == edge) {
                    matrix[cell.first][row.first] = matrix[row.first][cell.first] = {};
                    return *this;
                }
        throw std::logic_error(edge + " edge doesn't exist\n");

        return *this;
    }

    template<typename V, typename E>
    bool AdjacencyMatrix<V, E>::containEdge(const E &edge) const {
        for (const std::pair<const V, std::unordered_map<V, E>> &row: matrix)
            if (std::any_of(row.second.begin(), row.second.end(),
                            [&edge](const std::pair<V, E> &cell) -> bool {
                                return cell.second == edge;
                            }))
                return true;
        return false;
    }

    template<typename V, typename E>
    bool AdjacencyMatrix<V, E>::containVertex(const V &vertex) const {
        return matrix.contains(vertex);
    }

    template<typename V, typename E>
    size_t AdjacencyMatrix<V, E>::numVertices() {
        return matrix.size();
    }

    template<typename V, typename E>
    size_t AdjacencyMatrix<V, E>::numEdges() {
        return edges().size();
    }

    template<typename V, typename E>
    size_t AdjacencyMatrix<V, E>::outDegree(const V &vertex) {
        return outgoingEdges(vertex).size();
    }

    template<typename V, typename E>
    size_t AdjacencyMatrix<V, E>::inDegree(const V &vertex) {
        return outDegree(vertex);
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyMatrix<V, E>::print(std::ostream &ostream) {
        //For printing elements in unordered_map by order ;
        std::vector<V> vertices;
        for (const std::pair<const V, std::unordered_map<V, E>> &row: matrix) {
            ostream << '\t' << row.first;
            vertices.push_back(row.first);
        }
        ostream << '\n';
        for (const V &vertex1: vertices) {
            ostream << vertex1 << '\t';
            for (const V &vertex2: vertices)
                ostream << matrix[vertex1][vertex2] << '\t';
            ostream << '\n';
        }

        return *this;
    }
}

#endif