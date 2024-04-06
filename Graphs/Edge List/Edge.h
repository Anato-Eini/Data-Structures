#ifndef DATA_STRUCTURES_EDGE_H
#define DATA_STRUCTURES_EDGE_H

#include "Vertex.h"

class Edge {
    int weight;
    Vertex* destVertex;
public:
    Edge(int, Vertex*);
    int getWeight();
    Vertex* getDestVertex();
};


#endif //DATA_STRUCTURES_EDGE_H
