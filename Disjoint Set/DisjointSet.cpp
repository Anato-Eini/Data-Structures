#include <vector>
#ifndef DISJOINTSET_CPP
#define DISJOINTSET_CPP

#include "DisjointSet.h"

template <typename T>
DisjointSet<T>& DisjointSet<T>::create_set(std::pmr::vector<T>& vector)
{
    for(T & element : vector)
        map.emplace(element, {});

    return *this;
}


template <typename T>
DisjointSet<T> & DisjointSet<T>::create_set(T array[], const size_t size)
{
   for (size_t i = 0; i < size; i++)
      map.emplace(array[i], {});

    return *this;
}

template <typename T>
Node<T>& DisjointSet<T>::find(T element) const
{
    Node<T> & node = map.at(element);
    if(!node.element)
        return node;
    return node.element = find(node.element->name);
}

template <typename T>
void DisjointSet<T>::union_(T element1, T element2)
{
    Node<T> & node1 = find(element1), & node2 = find(element2);

    if(node1.size < node2.size)
    {
        node1.element = node2;
        node2.size += node1.size;
    }else
    {
        node2.element = node1;
        node1.size += node2.size;
    }
}

template <typename T>
void DisjointSet<T>::print(std::ostream& ostream) const
{
    std::pmr::vector<Node<T>> vector; //For printing nodes;
    for (const std::pair<const T, Node<T>> & element : map)
    {
        ostream << element.first << '\t';
        vector.emplace_back(element.second);
    }
    ostream << '\n';
    for(Node<T> & node : vector)
        ostream << node.name << '\t';
}


template<typename T>
std::ostream & operator << (std::ostream & ostream, DisjointSet<T> & disjoint_set)
{
    disjoint_set.print(ostream);
    return ostream;
}


#endif