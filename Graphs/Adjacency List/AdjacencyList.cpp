#include "AdjacencyList.h"

std::vector<std::string> AdjacencyList::vertices() const {
    return std::vector<std::string>();
}

std::vector<std::pair<std::string, Edge *>> AdjacencyList::edges() const {
    return std::vector<std::pair<std::string, Edge *>>();
}

std::pair<std::string, std::string> *AdjacencyList::endVertices(const std::string &edge) {
    return nullptr;
}

std::vector<std::pair<std::string, Edge *>> AdjacencyList::outgoingEdges(const std::string &vertex) {
    return std::vector<std::pair<std::string, Edge *>>();
}

std::vector<std::pair<std::string, Edge *>> AdjacencyList::incomingEdges(const std::string &vertex) {
    return std::vector<std::pair<std::string, Edge *>>();
}

std::string AdjacencyList::getEdge(const std::string &vertex1, const std::string &vertex2) {
    return std::string();
}

std::vector<std::string> AdjacencyList::opposite(const std::string &vertex) {
    return std::vector<std::string>();
}

void AdjacencyList::addVertex(const std::string &vertex) {

}

void
AdjacencyList::addEdge(const std::string &edge, int weight, const std::string &vertex1, const std::string &vertex2) {

}

void AdjacencyList::removeVertex(const std::string &vertex) {

}

void AdjacencyList::removeEdge(const std::string &edge) {

}

bool AdjacencyList::containEdge(const std::string &edge) const {
    return false;
}

bool AdjacencyList::containVertex(const std::string &vertex) const {
    return false;
}

int AdjacencyList::numVertices() {
    return 0;
}

int AdjacencyList::numEdges() {
    return 0;
}

int AdjacencyList::outDegree(const std::string &vertex) {
    return 0;
}

int AdjacencyList::inDegree(const std::string &vertex) {
    return 0;
}

std::ostream& operator<<(std::ostream&, AdjacencyList* adjacencyList){

}

std::ostream& operator<<(std::ostream&, AdjacencyList& adjacencyList){

}