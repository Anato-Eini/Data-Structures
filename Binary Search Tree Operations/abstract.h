#include "node.h"
class Tree {
public:
    virtual Node* insert(Node *n, int num) = 0;
    virtual Node* search(Node* n, int num) = 0;
    virtual Node* deleteNode(Node* n, int num) = 0;
    virtual int maxHeight(Node* n) = 0;
    virtual int height(Node* n, int num) = 0;
    virtual int depth(Node *n, int num) = 0;
    virtual void printI(Node*) = 0;
    virtual void printPO(Node*) = 0;
    virtual void printPR(Node*) = 0;
};