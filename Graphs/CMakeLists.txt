cmake_minimum_required(VERSION 3.28.1)

project(Graphs)

set(CMAKE_CXX_STANDARD 26)

add_executable(Graph
        "General Graph/Graph.h"
        "Adjacency List/AdjacencyList.cpp"
        "Adjacency List/AdjacencyList.h"
        "Edge List/EdgeList.cpp"
        "Edge List/EdgeList.h"
        "main.cpp"
        "Adjacency Map/AdjacencyMap.cpp"
        "Adjacency Map/AdjacencyMap.h"
        "General Graph/Graph.cpp"
        "Adjacency Matrix/AdjacencyMatrix.cpp"
        "Adjacency Matrix/AdjacencyMatrix.h"
)