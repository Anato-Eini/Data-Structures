#include "Graph.h"

std::ostream& operator<<(std::ostream& os, Graph* graph){
    graph->print(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, Graph& graph){
    graph.print(os);
    return os;
}