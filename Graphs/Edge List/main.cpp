#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unordered_set>

class Node;

class Edge {
private:
    int weight;
    Node* destVertex;

public:
    Edge(Node* dest, int w) : destVertex(dest), weight(w) {}

    Edge(Node* dest) : destVertex(dest), weight(1) {}

    int getWeight() {
        return weight;
    }

    Node* getDestVertex() {
        return destVertex;
    }
};

class Node {
private:
    std::string name;
    std::vector<Edge> edgeList;

public:
    Node(std::string name) : name(std::move(name)) {}

    std::string getName() {
        return name;
    }

    std::vector<Edge>& getEdges() {
        return edgeList;
    }
};

class Graph {
private:
    std::unordered_set<Node*> nodes;

public:
    Graph() {}

    Edge AddEdge(Node* v1, Node* v2, int weight) {
        return v1->getEdges().emplace_back(v2,
                                           weight), v2->getEdges().emplace_back(v1, weight);
    }

    bool AddVertex(Node* v) {
        return nodes.insert(v).second;
    }

    void printGraph() {
        for (Node* v : nodes) {
            std::cout << "vertex name: " << v->getName() << ":\n";
            for (Edge e : v->getEdges()) {
                std::cout << "destVertex: " << e.getDestVertex()->getName() << ", weight: " << e.getWeight() << "\n";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Graph ourGraph;

    // nodes
    Node v0("0");
    Node v1("1");
    Node v2("2");
    Node v3("3");

    ourGraph.AddVertex(&v0);
    ourGraph.AddVertex(&v1);
    ourGraph.AddVertex(&v2);
    ourGraph.AddVertex(&v3);

    // edges
    ourGraph.AddEdge(&v0, &v1, 2);
    ourGraph.AddEdge(&v1, &v2, 3);
    ourGraph.AddEdge(&v2, &v0, 1);
    ourGraph.AddEdge(&v2, &v3, 1);
    ourGraph.AddEdge(&v3, &v2, 4);

    ourGraph.printGraph();
}