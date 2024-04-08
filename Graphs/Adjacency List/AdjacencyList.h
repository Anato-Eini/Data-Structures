#ifndef DATA_STRUCTURES_ADJACENCYLIST_H
#define DATA_STRUCTURES_ADJACENCYLIST_H

#include "../Graph.h"

class AdjacencyList : private Graph{
public:
    std::vector<std::string> vertices() const override;

    std::vector<std::pair<std::string, Edge *>> edges() const override;

    std::pair<std::string, std::string> *endVertices(const std::string &edge) override;

    std::vector<std::pair<std::string, Edge *>> outgoingEdges(const std::string &vertex) override;

    std::vector<std::pair<std::string, Edge *>> incomingEdges(const std::string &vertex) override;

    std::string getEdge(const std::string &vertex1, const std::string &vertex2) override;

    std::vector<std::string> opposite(const std::string &vertex) override;

    void addVertex(const std::string &vertex) override;

    void addEdge(const std::string &edge, int weight, const std::string &vertex1, const std::string &vertex2) override;

    void removeVertex(const std::string &vertex) override;

    void removeEdge(const std::string &edge) override;

    bool containEdge(const std::string &edge) const override;

    bool containVertex(const std::string &vertex) const override;

    int numVertices() override;

    int numEdges() override;

    int outDegree(const std::string &vertex) override;

    int inDegree(const std::string &vertex) override;

    friend std::ostream& operator<<(std::ostream&, AdjacencyList* adjacencyList);

    friend std::ostream& operator<<(std::ostream&, AdjacencyList& adjacencyList);
};

std::ostream& operator<<(std::ostream&, AdjacencyList* adjacencyList);

std::ostream& operator<<(std::ostream&, AdjacencyList& adjacencyList);

#endif //DATA_STRUCTURES_ADJACENCYLIST_H
