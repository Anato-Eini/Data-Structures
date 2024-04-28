#include "AdjacencyMatrix.h"

std::vector<std::string> AdjacencyMatrix::vertices() const {
    std::vector<std::string> arrOfVertices;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arrOfVertices),
                   [](const std::pair<const std::string, std::unordered_map<std::string, std::string>> & pair)
                   -> std::string { return pair.first;});
    return arrOfVertices;
}

std::vector<std::string> AdjacencyMatrix::edges() const {
    std::vector<std::string> arrOfEdges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix){
        for(const std::pair<const std::string, std::string> &column : row.second){
            if(!std::any_of(arrOfEdges.begin(), arrOfEdges.end(),
                            [&row](const std::string &edge) -> bool {
                return std::any_of(row.second.begin(), row.second.end(),
                                   [&edge](const std::pair<const std::string, std::string> &cell) -> bool {
                    return cell.second == edge;
                });
            }))
                arrOfEdges.emplace_back(column.second);
        }
    }
    return arrOfEdges;
}

std::pair<std::string, std::string> AdjacencyMatrix::endVertices(const std::string &edge) {
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row: matrix){
        auto it = std::find_if(row.second.begin(), row.second.end(),
                               [&edge](const std::pair<const std::string, std::string> &cell) -> bool {
            return cell.second == edge;
        });
        if(it != row.second.end())
            return {row.first, it->first};
    }
    throw std::logic_error(edge + " edge doesn't exist\n");
}

std::vector<std::string> AdjacencyMatrix::outgoingEdges(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    std::vector<std::string> edges;
    std::transform(matrix[vertex].begin(), matrix[vertex].end(), std::back_inserter(edges),
                   [](const std::pair<std::string, std::string> &cell) -> std::string {

    });
    return std::vector<std::string>();
}

std::vector<std::string> AdjacencyMatrix::incomingEdges(const std::string &vertex) {
    return std::vector<std::string>();
}

std::string AdjacencyMatrix::getEdge(const std::string &vertex1, const std::string &vertex2) {
    return std::string();
}

std::vector<std::string> AdjacencyMatrix::opposite(const std::string &vertex) {
    return std::vector<std::string>();
}

void AdjacencyMatrix::addVertex(const std::string &vertex) {
    if(containVertex(vertex))
        throw std::logic_error(vertex + " vertex already exists\n");
    matrix[vertex] = {};
}

void AdjacencyMatrix::addEdge(const std::string &edge, const std::string &vertex1, const std::string &vertex2) {
    matrix[vertex2][vertex1] = matrix[vertex1][vertex2] = edge;
}

void AdjacencyMatrix::removeVertex(const std::string &vertex) {

}

void AdjacencyMatrix::removeEdge(const std::string &edge) {

}

bool AdjacencyMatrix::containEdge(const std::string &edge) const {
    return false;
}

bool AdjacencyMatrix::containVertex(const std::string &vertex) const {
    return false;
}

int AdjacencyMatrix::numVertices() {
    return 0;
}

int AdjacencyMatrix::numEdges() {
    return 0;
}

int AdjacencyMatrix::outDegree(const std::string &vertex) {
    return 0;
}

int AdjacencyMatrix::inDegree(const std::string &vertex) {
    return 0;
}

void AdjacencyMatrix::print(std::ostream &ostream) {

}
