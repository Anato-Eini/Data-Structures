#include "Vertex.h"
#include <utility>

Vertex::Vertex(std::string name): name(std::move(name)) {}

bool Vertex::contains(Edge* edge){
    for(Edge e: edges)
        if(&e == *&edge)
            return true;
    return false;
}

int Vertex::numEdges(){
    return edges.size();
}