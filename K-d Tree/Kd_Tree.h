#ifndef DATA_STRUCTURES_KD_TREE_H
#define DATA_STRUCTURES_KD_TREE_H


class Kd_Tree {
    struct Node{
        int * point;
        Node * next;
        Node * prev;

        Node(int point[]);
    };

public:
    Kd_Tree();

    Kd_Tree(const int k_dimension);

    void insertKey(int point[]);

    void searchKey(int point[]);

private:
    //Fields

    Node * root;

    int size;

    int k_dimension;
};


#endif //DATA_STRUCTURES_KD_TREE_H
