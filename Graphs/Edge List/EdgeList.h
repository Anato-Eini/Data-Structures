#ifndef DATA_STRUCTURES_EDGELIST_H
#define DATA_STRUCTURES_EDGELIST_H

#include "../Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <unordered_map>
#include <string>

class EdgeList : public Graph{
    std::unordered_map<std::string, Vertex> Vertices;
    std::unordered_map<std::string, Edge> Edges;
public:
    std::vector<Vertex> vertices() override;
    std::vector<Edge> edges() override;
    std::vector<Vertex> endVertices(Edge &e) override;
    std::vector<Edge> outgoingEdges(Vertex vertex) override;
    std::vector<Edge> incomingEdges(Vertex vertex) override;
    Edge *getEdge(Vertex &vertex, Vertex &vertex1) override;
    Vertex opposite(Vertex &vertex, Edge &edge) override;
    int numVertices() override;
    int numEdges() override;
    int outDegree(Vertex vertex) override;
    int inDegree(Vertex vertex) override;
};


#endif //DATA_STRUCTURES_EDGELIST_H
