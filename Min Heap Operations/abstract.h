#include <vector>
using namespace std;
class MinHeap {
public:
    virtual void insert( int new_num) = 0;
    virtual int peek() = 0;
    virtual void deleteNode(int num) = 0;
    virtual void printHeapTree() = 0;
    virtual int removeMin() = 0;
};