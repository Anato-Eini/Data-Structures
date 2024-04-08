# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.27.8)

project(Graphs)

set(CMAKE_CXX_STANDARD 23)

add_executable(Graph-Adjacency_List
        "Adjacency List/main.cpp"
        "Adjacency List/AdjacencyList.cpp"
        "Adjacency List/AdjacencyList.h"
        Graph.h
)

add_executable(Graph-Adjacency_Map
        "Adjacency Map/main.cpp"
        Graph.h
)

add_executable(Graph-Adjacency_Matrix
        "Adjacency Matrix/main.cpp"
        Graph.h
)

add_executable(Graph-Edge_List
        "main.cpp"
        "Edge List/EdgeList.cpp"
        "Edge List/EdgeList.h"
        Graph.h
)