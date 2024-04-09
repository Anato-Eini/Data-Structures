#include <typeinfo>

#include "Graph.h"
#include "../Edge List/EdgeList.h"
#include "../Adjacency List/AdjacencyList.h"

std::ostream& operator<<(std::ostream& os, Graph* graph){
    std::vector<std::string> vertices{graph->vertices()}, edges{graph->edges()};
    if(typeid(*graph) == typeid(EdgeList)){
        os << (Graph &) "Vertices";// ????? ERROR, Why cast to (Graph &) ??
        //EdgeList overloaded operator<< operations here
    }
    return os;
}

std::ostream& operator<<(std::ostream&, Graph& graph){
    std::vector<std::string> vertices{graph.vertices()}, edges{graph.edges()};
}