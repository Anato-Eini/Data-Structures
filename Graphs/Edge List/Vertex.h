#ifndef DATA_STRUCTURES_VERTEX_H
#define DATA_STRUCTURES_VERTEX_H

#include <vector>
#include <string>
#include "Edge.h"

class Vertex {
    std::string name;
    std::vector<Edge> edges;
public:
    explicit Vertex(std::string);
    bool contains(Edge*);
    int numEdges();
};


#endif //DATA_STRUCTURES_VERTEX_H
