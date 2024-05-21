#include "GraphAbstract.h"
namespace Graph{
    template<typename V, typename E>
    std::ostream &operator<<(std::ostream &os, Graph::GraphAbstract <V, E> *graph) {
        graph->print(os);
        return os;
    }

    template<typename V, typename E>
    std::ostream &operator<<(std::ostream &os, Graph::GraphAbstract <V, E> &graph) {
        graph.print(os);
        return os;
    }
}