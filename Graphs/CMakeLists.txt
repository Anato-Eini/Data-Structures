cmake_minimum_required(VERSION 3.28.1)

project(Graphs)

set(CMAKE_CXX_STANDARD 26)

add_executable(Graph
        "General Graph/GraphAbstract.h"
        "General Graph/GraphAbstract.cpp"
        "Adjacency List/AdjacencyList.h"
        "Adjacency List/AdjacencyList.cpp"
        "Edge List/EdgeList.h"
        "Edge List/EdgeList.cpp"
        "Adjacency Map/AdjacencyMap.h"
        "Adjacency Map/AdjacencyMap.cpp"
        "Adjacency Matrix/AdjacencyMatrix.h"
        "Adjacency Matrix/AdjacencyMatrix.cpp"
        "main.cpp"
)