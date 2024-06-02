#include "BTreeNode.h"

BTreeNode::BTreeNode(int capacity) : size(0), capacity(capacity - 1), children(new BTreeNode*[capacity]),
                                    parent(nullptr), elem(new int[capacity - 1]) {
    for (int i = 0; i < capacity; ++i)
        children[i] = nullptr;
}

BTreeNode::BTreeNode(int capacity, BTreeNode *parent) : size(0), capacity(capacity - 1),
                                            children(new BTreeNode*[capacity]), parent(parent), elem(new int[capacity - 1]){
    for (int i = 0; i < capacity; ++i)
        children[i] = nullptr;
}

bool BTreeNode::isFull() {
    return size == capacity;
}
void BTreeNode::insertNonLeaf(int key, BTreeNode* node) {
    int i;
    for (i = size - 1; i >= 0 && elem[i] > key; i--) {
        elem[i + 1] = elem[i];
        children[i + 2] = children[i + 1];
    }
    elem[++i] = key;
    children[i + 1] = node;
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
    BTreeNode* newSibling = new BTreeNode(capacity + 1), *parentNode;
    if(parent)
        parentNode = parent;
    else{
        parent = parentNode = new BTreeNode(capacity + 1);
        parentNode->children[0] = this;
    }
    newSibling->parent = parentNode;
    parentNode->insertNonLeaf(removeElem(capacity / 2), newSibling);
    moveHalf(newSibling);
}

int BTreeNode::removeElem(int index) {
    int element = elem[index];
    for(int i = index + 1; i < size; i++)
        elem[i - 1] = elem[i];
    size--;
    return element;
}

std::ostream &operator<<(std::ostream &os, BTreeNode *node) {
    node->printInorder(os, node);
    return os;
}

BTreeNode *BTreeNode::removeChild(int index) {
    BTreeNode* child = children[index];
    int i;
    for(i = index; i < capacity && children[i]; i++)
        children[i] = children[i + 1];
    children[i] = nullptr;
    return child;
}

void BTreeNode::printInorder(std::ostream& os, BTreeNode *node) {
    if(node){
        int i;
        for(i = 0; i < node->size; i++){
            printInorder(os, node->children[i]);
            os << node->elem[i] << " ";
        }
        printInorder(os, node->children[i]);
    }
}

bool BTreeNode::isEmpty() {
    return size == 0;
}

void BTreeNode::moveHalf(BTreeNode *node) {
    int i, j;
    for(i = capacity / 2, j = 0; i < size; i++, j++){
        node->elem[j] = elem[i];
        node->children[j] = children[i + 1];
        children[i + 1] = nullptr;
    }
    node->children[j] = children[i];
    node->size = capacity - (capacity / 2) - 1;
    children[i] = nullptr;
    size = capacity / 2;
}

void BTreeNode::deleteElem(int key) {
    for(int i = 0; i < size; i++)
        if(elem[i] == key) {
            for (++i; i < size; i++)
                elem[i - 1] = elem[i];
            size--;
            if(size < 2){

            }
            return;
        }
    throw std::logic_error(std::to_string(key) + " key doesn't exist\n");
}

int BTreeNode::getPosFromParent() {
    if(!parent)
        throw std::logic_error("Parent doesn't exist\n");
    BTreeNode* par = parent;
    for(int i = par->getSize(); i >= 0; i--)
        if(par->children[i] == this)
            return i;
    return -1;
}

std::pair<BTreeNode *, BTreeNode *> BTreeNode::getSiblings() {
    std::pair<BTreeNode *, BTreeNode *> sibling;
    int index = getPosFromParent();
    if(index + 1 == capacity + 1){
    }
    return std::pair<BTreeNode *, BTreeNode *>();
}
