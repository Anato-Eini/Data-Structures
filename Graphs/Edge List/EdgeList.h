#ifndef DATA_STRUCTURES_EDGELIST_H
#define DATA_STRUCTURES_EDGELIST_H

#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "Edge.h"

class EdgeList{
    std::unordered_set<std::string> Vertices;
    std::unordered_map<std::string, Edge*> Edges;
public:
    std::vector<std::string> vertices() const;
    std::vector<Edge*> edges() const;
    std::pair<std::string, std::string>* endVertices(const std::string&); //returns a pair of vertices from heap
    std::vector<Edge*> outgoingEdges(const std::string&);
    std::vector<Edge*> incomingEdges(const std::string&);
    Edge* getEdge(const std::string&, const std::string&);
    std::string opposite(const std::string&);
    void addVertex(const std::string&);
    void addEdge(const std::string&, int, const std::string&, const std::string&);
    void removeVertex(const std::string&);
    void removeEdge(const std::string&);
    int numVertices();
    int numEdges();
    int outDegree(const std::string&);
    int inDegree(const std::string&);
    friend std::ostream& operator<<(std::ostream&, EdgeList*);
    friend std::ostream& operator<<(std::ostream&, EdgeList&);
};

std::ostream& operator<<(std::ostream&, EdgeList*);
std::ostream& operator<<(std::ostream&, EdgeList&);

#endif //DATA_STRUCTURES_EDGELIST_H
