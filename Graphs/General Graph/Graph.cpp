#include <typeinfo>

#include "Graph.h"
#include "../Edge List/EdgeList.h"
#include "../Adjacency List/AdjacencyList.h"

std::ostream& operator<<(std::ostream& os, const Graph* graph){
    std::vector<std::string> vertices{graph->vertices()}, edges{graph->edges()};
    if(typeid(*graph) == typeid(EdgeList)){
        os << "Vertices";// ????? ERROR, Why cast to (Graph &) ??
        //EdgeList operator<< operations here
    }
    return os;
}
/*

std::ostream& operator<<(std::ostream&, Graph& graph){
    std::vector<std::string> vertices{graph.vertices()}, edges{graph.edges()};
}*/
