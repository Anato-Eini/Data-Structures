#include "BTreeNode.h"

BTreeNode::BTreeNode(int capacity) : size(0), capacity(capacity - 1), children(new BTreeNode*[capacity]), parent(nullptr) {
    for (int i = 0; i < capacity; ++i)
        children[i] = new BTreeNode{capacity};
}

BTreeNode::BTreeNode(int capacity, BTreeNode *parent) : size(0), capacity(capacity - 1), children(new BTreeNode*[capacity]), parent(parent){
    for (int i = 0; i < capacity; ++i)
        children[i] = new BTreeNode{capacity};
}

bool BTreeNode::isFull() {
    return size == capacity;
}

void BTreeNode::insertElem(int key) {
    int i;
    for(i = size - 1; elem[i] > key; i--)
        elem[i + 1] = elem[i];
    elem[i] = key;
    size++;
    if(isFull())
        splitNode();
}

int BTreeNode::getCapacity() const {
    return capacity;
}

int BTreeNode::getSize() const {
    return size;
}

BTreeNode* BTreeNode::getChild(int key) {
    int i;
    for(i = 0; i < size; i++)
        if(elem[i] > key)
            return children[i];
    return children[i];
}

void BTreeNode::splitNode() {
    if(parent) {
        parent->insertElem(removeElem(capacity / 2));

    }else{
        BTreeNode* newRoot = new BTreeNode(capacity), *newSibling = new BTreeNode(capacity, newRoot);
        newRoot->insertElem(removeElem(capacity / 2));
        int i = capacity / 2;
        while(i < size)
            newSibling->insertElem(removeElem(i));
        parent = newRoot;
    }
}

int BTreeNode::removeElem(int index) {
    int element = elem[index];
    for(int i = index + 1; i < size; i++)
        elem[i - 1] = elem[i];
    size--;
    return element;
}

std::ostream &operator<<(std::ostream &os, BTreeNode *node) {

    return os;
}

void BTreeNode::insertLastChild(BTreeNode *child) {

}


