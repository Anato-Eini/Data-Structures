#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H

#include <vector>
#include <string>

class Edge;
class Graph{
    virtual std::vector<std::string> vertices() const = 0;
    virtual std::vector<std::pair<std::string, Edge*>> edges() const = 0;
    //Returns a pair of vertices from heap. Nullptr if none
    virtual std::pair<std::string, std::string>* endVertices(const std::string& edge) = 0;
    virtual std::vector<std::pair<std::string, Edge*>> outgoingEdges(const std::string& vertex) = 0;
    virtual std::vector<std::pair<std::string, Edge*>> incomingEdges(const std::string& vertex) = 0;
    virtual std::string getEdge(const std::string& vertex1, const std::string& vertex2) = 0;
    virtual std::vector<std::string> opposite(const std::string& vertex) = 0;
    virtual void addVertex(const std::string& vertex) = 0;
    virtual void addEdge(const std::string& edge, int weight, const std::string& vertex1,
                         const std::string& vertex2) = 0;
    virtual void removeVertex(const std::string& vertex) = 0;
    virtual void removeEdge(const std::string& edge) = 0;
    virtual bool containEdge(const std::string& edge) const = 0;
    virtual bool containVertex(const std::string& vertex) const = 0;
    virtual int numVertices() = 0;
    virtual int numEdges() = 0;
    //Returns the number of outgoing edges. Return -1 if vertex doesn't exist
    virtual int outDegree(const std::string& vertex) = 0;
    //Returns the number of incoming edges. Return -1 if vertex doesn't exist
    virtual int inDegree(const std::string& vertex) = 0;
};

#endif //DATA_STRUCTURES_GRAPH_H
