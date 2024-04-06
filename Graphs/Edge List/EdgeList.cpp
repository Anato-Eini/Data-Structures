#include "EdgeList.h"

std::vector<Vertex> EdgeList::vertices() {
    return std::vector<Vertex>();
}

std::vector<Edge> EdgeList::edges() {
    return std::vector<Edge>();
}

std::vector<Vertex> EdgeList::endVertices(Edge &e) {
    return std::vector<Vertex>();
}

std::vector<Edge> EdgeList::outgoingEdges(Vertex vertex) {
    return std::vector<Edge>();
}

std::vector<Edge> EdgeList::incomingEdges(Vertex vertex) {
    return std::vector<Edge>();
}

Edge *EdgeList::getEdge(Vertex &vertex, Vertex &vertex1) {
    return nullptr;
}

Vertex EdgeList::opposite(Vertex &vertex, Edge &edge) {
    return Vertex();
}

int EdgeList::numVertices() {
    return 0;
}

int EdgeList::numEdges() {
    return 0;
}

int EdgeList::outDegree(Vertex vertex) {
    return 0;
}

int EdgeList::inDegree(Vertex vertex) {
    return 0;
}
