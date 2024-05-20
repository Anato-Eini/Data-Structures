cmake_minimum_required(VERSION 3.28.1)
project(Hash-Tables)

set(CMAKE_CXX_STANDARD 26)

add_executable(HashTable__Double_Hashing_
        "Open Addressing (Double Hashing)/HashTable.cpp"
        "Open Addressing (Double Hashing)/main.cpp"
        "Open Addressing (Double Hashing)/Stack.h"
        "Open Addressing (Double Hashing)/Stack.cpp"
        "Open Addressing (Double Hashing)/HashTable.h"
        "Open Addressing (Double Hashing)/Node.h"
)

add_executable(HashTable__Linear_Probing_
        "Open Addressing (Linear Probing)/HashTable.cpp"
        "Open Addressing (Linear Probing)/Node.h"
        "Open Addressing (Linear Probing)/Stack.h"
        "Open Addressing (Linear Probing)/main.cpp"
        "Open Addressing (Linear Probing)/HashTable.h"
        "Open Addressing (Linear Probing)/Stack.cpp"
)

add_executable(HashTable__Quadratic_Probing_
        "Open Addressing (Quadratic Probing)/HashTable.cpp"
        "Open Addressing (Quadratic Probing)/Stack.h"
        "Open Addressing (Quadratic Probing)/Node.h"
        "Open Addressing (Quadratic Probing)/main.cpp"
        "Open Addressing (Quadratic Probing)/HashTable.h"
        "Open Addressing (Quadratic Probing)/Stack.cpp"
)

add_executable(HashTable__Open_Hashing_
        "Separate Chaining (Open Hashing)/AVLTree.cpp"
        "Separate Chaining (Open Hashing)/Stack.h"
        "Separate Chaining (Open Hashing)/Node.h"
        "Separate Chaining (Open Hashing)/HashTable.h"
        "Separate Chaining (Open Hashing)/AVLTree.h"
        "Separate Chaining (Open Hashing)/Stack.cpp"
        "Separate Chaining (Open Hashing)/HashTable.cpp"
        "Separate Chaining (Open Hashing)/main.cpp"
)