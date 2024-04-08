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
    std::vector<std::pair<std::string, Edge*>> edges() const;
     //Returns a pair of vertices from heap. Nullptr if none
    std::pair<std::string, std::string>* endVertices(const std::string&);
    std::vector<std::pair<std::string, Edge*>> outgoingEdges(const std::string&);
    std::vector<std::pair<std::string, Edge*>> incomingEdges(const std::string&);
    std::string getEdge(const std::string&, const std::string&);
    std::vector<std::string> opposite(const std::string&);
    void addVertex(const std::string&);
    void addEdge(const std::string&, int, const std::string&, const std::string&);
    void removeVertex(const std::string&);
    void removeEdge(const std::string&);
    bool containEdge(const std::string&) const;
    bool containVertex(const std::string&) const;
    int numVertices();
    int numEdges();
    //Returns number of outgoing edges. Return -1 if vertex doesn't exist
    int outDegree(const std::string&);
    //Returns number of incoming edges. Return -1 if vertex doesn't exist
    int inDegree(const std::string&);
    ~EdgeList();
    friend std::ostream& operator<<(std::ostream&, EdgeList*);
    friend std::ostream& operator<<(std::ostream&, EdgeList&);
};

std::ostream& operator<<(std::ostream&, EdgeList*);
std::ostream& operator<<(std::ostream&, EdgeList&);

#endif //DATA_STRUCTURES_EDGELIST_H
