#include "node.h"
class AbstractPriorityQueue{
public:
    virtual void enqueue(int num, int priority) = 0;
    virtual int dequeue() = 0;
    virtual bool exists(int num) = 0;
};