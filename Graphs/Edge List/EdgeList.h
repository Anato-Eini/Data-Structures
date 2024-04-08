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

    std::pair<std::string, std::string>* endVertices(const std::string& edge);

    std::vector<std::pair<std::string, Edge*>> outgoingEdges(const std::string& vertex);

    std::vector<std::pair<std::string, Edge*>> incomingEdges(const std::string& vertex);

    std::string getEdge(const std::string& vertex1, const std::string& vertex2);

    std::vector<std::string> opposite(const std::string& vertex);

    void addVertex(const std::string& vertex);

    void addEdge(const std::string& edge, int weight, const std::string& vertex1, const std::string& vertex2);

    void removeVertex(const std::string& vertex);

    void removeEdge(const std::string& edge);

    bool containEdge(const std::string& edge) const;

    bool containVertex(const std::string& vertex) const;

    int numVertices();

    int numEdges();

    int outDegree(const std::string& vertex);

    int inDegree(const std::string& vertex);

    ~EdgeList();

    friend std::ostream& operator<<(std::ostream&, EdgeList*);

    friend std::ostream& operator<<(std::ostream&, EdgeList&);

};

std::ostream& operator<<(std::ostream&, EdgeList*);

std::ostream& operator<<(std::ostream&, EdgeList&);

#endif //DATA_STRUCTURES_EDGELIST_H
