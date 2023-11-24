#include "Node.h"
class Abstract{
public:
    virtual Node* insertNode(Node*, int) = 0;
    virtual Node* deleteNode(Node*, int) = 0;
    virtual Node* searchNode(Node*, int) = 0;
    virtual int depth(Node*, int) = 0;
    virtual int height(Node*) = 0;
    virtual void printI(Node*) = 0;
    virtual void printPO(Node*) = 0;
    virtual void printPR(Node*) = 0;
};