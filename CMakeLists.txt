cmake_minimum_required(VERSION 3.28.1)
project(Data-Structures)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(Hash-Tables)

add_subdirectory(Graphs)

add_subdirectory(Stack)

add_executable(AVL_Tree
        "AVL Tree/AVLTree.cpp"
        "AVL Tree/Node.h"
        "AVL Tree/AVLTree.h"
        "AVL Tree/main.cpp"
)

add_executable(B_Tree
        "B Tree/main.cpp"
        "B Tree/BTreeNode.cpp"
        "B Tree/BTreeNode.h"
        "B Tree/BTree.cpp"
        "B Tree/BTree.h"
)

add_executable(Expression_Tree
        "Expression Tree/Abstract.h"
        "Expression Tree/TreeNode.h"
        "Expression Tree/Stack.h"
        "Expression Tree/main.cpp"
)

add_executable(PriorityQueueMaxHeap
        "Implementing Priority Queues with Max Heap/abstract.h"
        "Implementing Priority Queues with Max Heap/main.cpp"
        "Implementing Priority Queues with Max Heap/PriorityQueue.h"
        "Implementing Priority Queues with Max Heap/node.h"
)

add_executable(MinHeap
        "Min Heap Operations/abstract.h"
        "Min Heap Operations/main.cpp"
        "Min Heap Operations/MinHeap.h"
)

add_executable(Queue
        "Queue/Deque.cpp"
        "Queue/queue.cpp"
)

add_executable(Red_Black_Tree
        "Red-Black Tree/main.cpp"
        "Red-Black Tree/Node.h"
        "Red-Black Tree/RedBlackTree.h"
        "Red-Black Tree/RedBlackTree.cpp"
)

add_executable(Splay_Tree
        "Splay Tree/SplayTree.h"
        "Splay Tree/SplayTree.cpp"
        "Splay Tree/Node.h"
        "Splay Tree/main.cpp"
)

add_executable(Binary_Search_Tree
        "Binary Search Tree/main.cpp"
        "Binary Search Tree/Node.h"
        "Binary Search Tree/BinarySearchTree.cpp"
        "Binary Search Tree/BinarySearchTree.h"
)
add_executable(Trie "Trie Tree/Trie.cpp" "Trie Tree/Trie.h"
        "Trie Tree/Node.h"
        "Trie Tree/main.cpp")
add_executable(Segment_Tree
        "Segment Tree/SegmentTree.cpp"
        "Segment Tree/SegmentTree.h"
        "Segment Tree/Node.h"
)
add_executable(Fenwick_Tree
        "Fenwick Tree/FenwickTree.cpp"
        "Fenwick Tree/FenwickTree.h"
)

add_executable(Disjoint_Set
        "Disjoint Set/DisjointSet.cpp"
        "Disjoint Set/DisjointSet.h"
)