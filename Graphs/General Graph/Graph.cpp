#include <typeinfo>

#include "Graph.h"
#include "../Edge List/EdgeList.h"
#include "../Adjacency List/AdjacencyList.h"

std::ostream& operator<<(std::ostream& os, Graph* graph){
    graph->print(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, Graph& graph){
    graph.print(os);
    return os;
}