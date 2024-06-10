#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

#include "unordered_map"
#include "ostream"

#include "Node.h"

template <typename T>
class DisjointSet {
    std::unordered_map<T, Node<T>> map;

    void print(std::ostream & ostream) const;
public:

    DisjointSet & create_set(T array[], size_t size);

    DisjointSet & create_set(std::pmr::vector<T> & vector);

    Node<T> & find(T element) const;

    void union_(T element1, T element2);

    friend std::ostream & operator<< <T> (std::ostream & ostream, DisjointSet & disjoint_set);
};

template <typename T>
std::ostream & operator<< (std::ostream & ostream, DisjointSet<T> & disjoint_set);

#include "DisjointSet.cpp"

#endif //DISJOINTSET_H
