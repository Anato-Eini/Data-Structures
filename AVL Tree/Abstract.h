#include "Node.h"
class Abstract{
public:
    virtual Node* insertNode(Node*, int) = 0;
    virtual Node* deleteNode(Node*, int) = 0;
    virtual Node* searchNode(Node*, int) = 0;
    virtual int depth(Node*) = 0;
    virtual int height(Node*) = 0;
    virtual int maxHeight(Node*) = 0;
    virtual void print() = 0;
};