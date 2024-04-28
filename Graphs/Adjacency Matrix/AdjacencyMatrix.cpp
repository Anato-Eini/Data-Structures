#include "AdjacencyMatrix.h"

std::vector<std::string> AdjacencyMatrix::vertices() const {
    std::vector<std::string> arrOfVertices;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arrOfVertices),
                   [](const std::pair<const std::string, std::unordered_map<std::string, std::string>> & pair) -> std::string {
        return pair.first;
    });
    return arrOfVertices;
}

std::vector<std::string> AdjacencyMatrix::edges() const {
    std::vector<std::string> arrOfEdges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &pair : matrix){

    }
    return std::vector<std::string>();
}

std::pair<std::string, std::string> AdjacencyMatrix::endVertices(const std::string &edge) {
    return std::pair<std::string, std::string>();
}

std::vector<std::string> AdjacencyMatrix::outgoingEdges(const std::string &vertex) {
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

}

void AdjacencyMatrix::addEdge(const std::string &edge, const std::string &vertex1, const std::string &vertex2) {

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
