#ifndef DATA_STRUCTURES_KD_TREE_H
#define DATA_STRUCTURES_KD_TREE_H


class Kd_Tree {
    struct Node{
        int * point;
        Node * next;
        Node * prev;
    };

public:
    Kd_Tree();

    Kd_Tree(const int k_dimension);

    void insertKey(/* Maybe use variadic template? */);

private:
    //Fields

    Node * root;

    int size;

    int k_dimension;
};


#endif //DATA_STRUCTURES_KD_TREE_H
