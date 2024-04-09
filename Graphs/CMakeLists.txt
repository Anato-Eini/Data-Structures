cmake_minimum_required(VERSION 3.27.8)

project(Graphs)

set(CMAKE_CXX_STANDARD 23)

add_executable(Graph
        "General Graph/Graph.h"
        "Adjacency List/AdjacencyList.cpp"
        "Adjacency List/AdjacencyList.h"
        "Edge List/EdgeList.cpp"
        "Edge List/EdgeList.h"
        "main.cpp"
        "General Graph/Graph.cpp"
)