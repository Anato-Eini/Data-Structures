#include "Edge.h"

std::ostream& operator<<(std::ostream& os, Edge* edge){
    os << "Weight: "<< edge->weight << " - <" << edge->pairVertex.first << ", " << edge->pairVertex.second << ">";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Edge& edge){
    os << "Weight: "<< edge.weight << " - <" << edge.pairVertex.first << ", " << edge.pairVertex.second << ">";
    return os;
}
