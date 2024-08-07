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

    void print(std::ostream & ostream) const;

public:
    Kd_Tree();

    explicit Kd_Tree(const int k_dimension);

    void insertKey(const int point[]);

    void insertKey(const std::vector<int> & point);

    void keyExist(const int point[]) const;

    void keyExist(const std::vector<int> & point) const;

    void deleteKey(const int point[]);

    void deleteKey(const std::vector<int> & point);


private:
    //Fields

    Node * root;

    int size;

    int k_dimension;

    friend std::ostream & operator<<(std::ostream & ostream, const Kd_Tree * tree);

    friend std::ostream & operator<<(std::ostream & ostream, const Kd_Tree & tree);
};

std::ostream & operator<<(std::ostream & ostream, const Kd_Tree * tree);

std::ostream & operator<<(std::ostream & ostream, const Kd_Tree & tree);

#endif //DATA_STRUCTURES_KD_TREE_H
