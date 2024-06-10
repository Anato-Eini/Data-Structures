#include "iostream"

#include "DisjointSet.h"

int main()
{
    DisjointSet<int> disjoint_set;
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    disjoint_set.create_set(array, 8);
    disjoint_set.union_(6, 4);
    disjoint_set.union_(5, 6);
    disjoint_set.union_(4, 5);
    disjoint_set.union_(4, 3);
    disjoint_set.union_(4, 7);
    std::cout << disjoint_set;
    return 0;
}