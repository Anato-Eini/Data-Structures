#include "Abstract.h"
class RedBlackTree: public Abstract{
    static Node* createNode(Node* parent, int num){
        return new Node{num, false, nullptr, nullptr, parent};
    }
    static Node* rotateLeft(Node* node){
        Node* left = node->left, *leftRight = node->left->right;
        left->parent = node->parent;
        left->right = node;
        node->parent = left;
        node->right = leftRight;
        leftRight->parent = node;
        return left;
    }
    static Node* rotateRight(Node* node){
        Node* right = node->right, *rightLeft = node->right->left;

    }
public:
};