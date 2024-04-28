#include "AdjacencyMatrix.h"

std::vector<std::string> AdjacencyMatrix::vertices() const {
    std::vector<std::string> arrOfVertices;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arrOfVertices),
                   [](const std::pair<const std::string, std::unordered_map<std::string, std::string>> & pair)
                   -> std::string { return pair.first; });
    return arrOfVertices;
}

std::vector<std::string> AdjacencyMatrix::edges() const {
    std::unordered_set<std::string> edgeSet; // For faster look-up
    std::vector<std::string> arrOfEdges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix)
        for(const std::pair<const std::string, std::string> &column : row.second)
            if(!edgeSet.contains(column.second))
                edgeSet.insert(column.second);
    edgeSet.erase("");
    std::transform(edgeSet.begin(), edgeSet.end(), std::back_inserter(arrOfEdges),
                   [](const std::string &s) -> std::string { return s; });
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
    for(const std::pair<const std::string, std::string> &cell : matrix[vertex])
        if(!cell.second.empty())
            edges.push_back(cell.second);
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
    for(const std::pair<const std::string, std::string> &row : matrix[vertex])
        if(!row.second.empty())
            vertices.push_back(row.first);
    return vertices;
}

void AdjacencyMatrix::addVertex(const std::string &vertex) {
    if(containVertex(vertex))
        throw std::logic_error(vertex + " vertex already exists\n");
    matrix[vertex] = {};
    for(std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix)
        matrix[vertex][row.first] = row.second[vertex] = "";
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
                matrix[cell.first][row.first] = matrix[row.first][cell.first] = "";
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
    //For printing elements in unordered_map by order ;
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &row : matrix) {
        ostream << '\t' << row.first;
        vertices.push_back(row.first);
    }
    ostream << '\n';
    for(const std::string &vertex1 : vertices){
        ostream << vertex1 << '\t';
        for(const std::string &vertex2 : vertices)
            ostream << matrix[vertex1][vertex2] << '\t';
        ostream << '\n';
    }
}
