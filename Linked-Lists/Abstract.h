#include "Node.h"
class SinglyList{
public:
    virtual void addLast(int) = 0;
    virtual void addFirst(int) = 0;
    virtual void print() = 0;
    virtual void removeNode(int) = 0;
    virtual void removeAt(int) = 0;
    virtual void flip() = 0;
    virtual void addAt(int num, int pos) = 0;
    virtual void rotateNodes() = 0;//solves the problem of https://citu.codechum.com/student/study-area/5593
    virtual void sortList() = 0;//solves the problem https://citu.codechum.com/student/study-area/5606
    virtual int getSize() = 0;
    virtual int mostRepeatedElement() = 0;
    virtual bool isPresent(int num) = 0;
};

class DoublyList{
public:
    virtual void addLast(int) = 0;
    virtual void addFirst(int) = 0;
    virtual void print() = 0;
    virtual int nthNodeFromLast(int) = 0;//this solves the problem of https://citu.codechum.com/student/study-area/5591
    virtual bool isPalindrome() = 0;// solves the problem of https://citu.codechum.com/student/study-area/5685
};