#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H
#include <vector>

class Vertex;
class Edge;

class Graph{
public:
    virtual std::vector<Vertex> vertices() = 0;
    virtual std::vector<Edge> edges() = 0;
    virtual std::vector<Vertex> endVertices(Edge& e) = 0;
    virtual std::vector<Edge> outgoingEdges(Vertex) = 0;
    virtual std::vector<Edge> incomingEdges(Vertex) = 0;
    virtual Edge* getEdge(Vertex &, Vertex &) = 0;
    virtual Vertex opposite(Vertex &, Edge &) = 0;
    virtual int numVertices() = 0;
    virtual int numEdges() = 0;
    virtual int outDegree (Vertex) = 0;
    virtual int inDegree(Vertex) = 0;
};

#endif //DATA_STRUCTURES_GRAPH_H
