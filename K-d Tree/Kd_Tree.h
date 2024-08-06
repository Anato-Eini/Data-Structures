#ifndef DATA_STRUCTURES_KD_TREE_H
#define DATA_STRUCTURES_KD_TREE_H

#include "vector"
#include "ostream"

class Kd_Tree {

    struct Node{
        int * point;

        Node * right;

        Node * left;

        explicit Node(const int point[]);

        explicit Node(const std::vector<int> & point);

        ~Node();
    };

    void print(std::ostream & ostream, Node * node, std::string && indent, bool isLeaf) const;

public:
    Kd_Tree();

    explicit Kd_Tree(const int k_dimension);

    void insertKey(const int point[]);

    void insertKey(const std::vector<int> & point);

    void searchKey(const int point[]) const;

    void searchKey(const std::vector<int> & point) const;


private:
    //Fields

    Node * root;

    int size;

    int k_dimension;

    friend std::ostream & operator<<(std::ostream & ostream, const Kd_Tree * tree);

    friend std::ostream & operator<<(std::ostream & ostream, const Kd_Tree & tree);
};

std::ostream & operator<<(std::ostream & ostream, const Kd_Tree * tree){
    tree->print(ostream);

    return ostream;
}

std::ostream & operator<<(std::ostream & ostream, const Kd_Tree & tree){
    tree.print(ostream);

    return ostream;
}

#endif //DATA_STRUCTURES_KD_TREE_H
