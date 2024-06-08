cmake_minimum_required(VERSION 3.28.1)

project(Data-Structures)
set(CMAKE_CXX_STANDARD 26)

add_executable(ArrayStack ArrayStack/ArrayStack.cpp ArrayStack/ArrayStack.h
)

add_executable(LinkedListStack
        LinkedListStack/LinkedListStack.cpp
        LinkedListStack/LinkedListStack.h
)