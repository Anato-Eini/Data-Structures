#ifndef DATA_STRUCTURES_EDGE_H
#define DATA_STRUCTURES_EDGE_H

#include <ostream>

struct Edge{
    std::pair<std::string, std::string> pairVertex;
    int weight;
    friend std::ostream& operator<<(std::ostream&, Edge*);
    friend std::ostream& operator<<(std::ostream&, const Edge&);
};

std::ostream& operator<<(std::ostream&, Edge*);
std::ostream& operator<<(std::ostream&, const Edge&);

#endif //DATA_STRUCTURES_EDGE_H
