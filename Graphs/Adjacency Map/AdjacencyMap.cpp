#include "AdjacencyMap.h"

std::vector<std::string> AdjacencyMap::vertices() const {
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &p : Vertices)
        vertices.emplace_back(p.first);
    return vertices;
}

std::vector<std::string> AdjacencyMap::edges() const {
    std::vector<std::string> edges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &p : Vertices)
        for(const std::pair<const std::string, std::string> &vertexEdge: p.second)
            edges.emplace_back(vertexEdge.second);
    return edges;
}

std::pair<std::string, std::string> AdjacencyMap::endVertices(const std::string &edge) {

    return std::pair<std::string, std::string>();
}

std::vector<std::string> AdjacencyMap::outgoingEdges(const std::string &vertex) {
    return std::vector<std::string>();
}

std::vector<std::string> AdjacencyMap::incomingEdges(const std::string &vertex) {
    return std::vector<std::string>();
}

std::string AdjacencyMap::getEdge(const std::string &vertex1, const std::string &vertex2) {
    return std::string();
}

std::vector<std::string> AdjacencyMap::opposite(const std::string &vertex) {
    return std::vector<std::string>();
}

void AdjacencyMap::addVertex(const std::string &vertex) {

}

void AdjacencyMap::addEdge(const std::string &edge, const std::string &vertex1, const std::string &vertex2) {

}

void AdjacencyMap::removeVertex(const std::string &vertex) {

}

void AdjacencyMap::removeEdge(const std::string &edge) {

}

bool AdjacencyMap::containEdge(const std::string &edge) const {
    return false;
}

bool AdjacencyMap::containVertex(const std::string &vertex) const {
    return false;
}

int AdjacencyMap::numVertices() {
    return 0;
}

int AdjacencyMap::numEdges() {
    return 0;
}

int AdjacencyMap::outDegree(const std::string &vertex) {
    return 0;
}

int AdjacencyMap::inDegree(const std::string &vertex) {
    return 0;
}

void AdjacencyMap::print(std::ostream &ostream) {

}
