#include "Edge.h"

Edge::Edge(int weight, Vertex* vertex): weight(weight), destVertex(vertex){}
int Edge::getWeight(){
    return weight;
}
Vertex* Edge::getDestVertex(){
    return destVertex;
}