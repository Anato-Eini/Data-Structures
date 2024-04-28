#include "AdjacencyMatrix.h"

std::vector<std::string> AdjacencyMatrix::vertices() const {
    std::vector<std::string> arrOfVertices;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arrOfVertices),
                   [](const std::pair<const std::string, std::unordered_map<std::string, std::string>> & pair)
                   -> std::string { return pair.first; });
    return arrOfVertices;
}

std::vector<std::string> AdjacencyMatrix::edges() const {
    std::unordered_set<std::string> edgeSet;
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
        return cell.second;
    });
    return edges;
}

std::vector<std::string> AdjacencyMatrix::incomingEdges(const std::string &vertex) {
    return outgoingEdges(vertex);
}

std::string AdjacencyMatrix::getEdge(const std::string &vertex1, const std::string &vertex2) {
    if(!containVertex(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exist\n");
    else if(!containVertex(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exist\n");
    return matrix[vertex1][vertex2];
}

std::vector<std::string> AdjacencyMatrix::opposite(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::string> &row : matrix[vertex]){
        if(row.first != vertex)
            vertices.push_back(row.second);
    }
    return vertices;
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
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    matrix.erase(vertex);
    for (std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix)
        row.second.erase(vertex);
}

void AdjacencyMatrix::removeEdge(const std::string &edge) {
    for(std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix)
        for(std::pair<const std::string, std::string> &cell : row.second)
            if(cell.second == edge){
                matrix[row.first].erase(cell.first);
                matrix[cell.first].erase(row.first);
                return;
            }
    throw std::logic_error(edge + " edge doesn't exist\n");
}

bool AdjacencyMatrix::containEdge(const std::string &edge) const {
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix)
        if(std::any_of(row.second.begin(), row.second.end(),
                               [&edge](const std::pair<std::string, std::string> &cell) -> bool {
            return cell.second == edge;
        }))
            return true;
    return false;
}

bool AdjacencyMatrix::containVertex(const std::string &vertex) const {
    return matrix.contains(vertex);
}

int AdjacencyMatrix::numVertices() {
    return matrix.size();
}

int AdjacencyMatrix::numEdges() {
    return edges().size();
}

int AdjacencyMatrix::outDegree(const std::string &vertex) {
    return outgoingEdges(vertex).size();
}

int AdjacencyMatrix::inDegree(const std::string &vertex) {
    return outDegree(vertex);
}

void AdjacencyMatrix::print(std::ostream &ostream) {
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix)
        ostream << '\t' << row.first;
    ostream << '\n';
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix){
        ostream << row.first << '\t';
        for(const std::pair<const std::string, std::string> &cell : row.second)
            ostream << cell.second << '\t';
    }
}
