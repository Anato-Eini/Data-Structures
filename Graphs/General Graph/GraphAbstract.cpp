#include "GraphAbstract.h"

namespace Graph{
    template<typename V, typename E>
    std::ostream &operator<<(std::ostream &os, GraphAbstract <V, E> *graph) {
        graph->print(os);
        return os;
    }

    template<typename V, typename E>
    std::ostream &operator<<(std::ostream &os, GraphAbstract <V, E> &graph) {
        graph.print(os);
        return os;
    }

    // Explicit instantiation
    template std::ostream &operator<< <std::string, std::string>(std::ostream &, GraphAbstract<std::string, std::string> *);
    template std::ostream &operator<< <std::string, std::string>(std::ostream &, GraphAbstract<std::string, std::string> &);
}