#include "Graph.h"

template <typename V, typename E>
std::ostream& operator<<(std::ostream& os, Graph<V, E>* graph){
    graph->print(os);
    return os;
}

template <typename V, typename E>
std::ostream& operator<<(std::ostream& os, Graph<V, E>& graph){
    graph.print(os);
    return os;
}