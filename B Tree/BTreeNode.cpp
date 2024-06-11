#include "BTreeNode.h"

BTreeNode::BTreeNode(const int & capacity, const bool & isLeaf) : size(0), capacity(capacity - 1),
                                    elem(new int[capacity - 1]), children(new BTreeNode*[capacity]), parent(nullptr),
                                    isLeaf(isLeaf)
{
    for (int i = 0; i < capacity; ++i)
        children[i] = nullptr;
}

BTreeNode::BTreeNode(const int & capacity, BTreeNode *parent, const bool & isLeaf) : size(0), capacity(capacity - 1),
                                            elem(new int[capacity - 1]), children(new BTreeNode*[capacity]),
                                            parent(parent), isLeaf(isLeaf)
{
    for (int i = 0; i < capacity; ++i)
        children[i] = nullptr;
}

bool BTreeNode::isFull() const {
    return size == capacity;
}

void BTreeNode::insert(const int & key) {
    int i;
    for (i = size - 1; i >= 0 && elem[i] > key; i--)
        elem[i + 1] = elem[i];

    elem[++i] = key;
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

BTreeNode* BTreeNode::getChild(const int & key) const
{
    int i;
    for(i = 0; i < size; i++)
        if(elem[i] > key)
            return children[i];
    return children[i];
}

void BTreeNode::splitNode() {
    BTreeNode* newSibling = new BTreeNode(capacity + 1, isLeaf), *parentNode;

    if(parent)
        parentNode = parent;
    else{
        parent = parentNode = new BTreeNode(capacity + 1, false);
        parentNode->children[0] = this;
    }

    newSibling->parent = parentNode;
    parentNode->insertFromChild(removeElem(capacity / 2), newSibling);
    moveHalf(newSibling);
}

void BTreeNode::insertFromChild(const int& key, BTreeNode* newChild)
{
    int i;
    for(i = size - 1; i >= 0 && elem[i] > key; i--)
    {
        elem[i + 1] = elem[i];
        children[i + 2] = children[i + 1];
    }
    elem[++i] = key;
    children[i + 1] = children[i];
    children[i] = newChild;
    size++;
    if(isFull())
        splitNode();
}


int BTreeNode::removeElem(const int & index) {
    const int element = elem[index];
    for(int i = index + 1; i < size; i++)
        elem[i - 1] = elem[i];
    size--;
    return element;
}

std::ostream &operator<<(std::ostream &os, BTreeNode *node) {
    node->printInorder(os, node);
    return os;
}

BTreeNode *BTreeNode::removeChild(const int & index) const
{
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

bool BTreeNode::isEmpty() const {
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

void BTreeNode::deleteElem(const int & key) {
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

int BTreeNode::getPosFromParent() const {
    if(!parent)
        throw std::logic_error("Parent doesn't exist\n");
    const BTreeNode* par = parent;
    for(int i = par->getSize(); i >= 0; i--)
        if(par->children[i] == this)
            return i;
    return -1;
}

std::pair<BTreeNode *, BTreeNode *> BTreeNode::getSiblings() const
{
    std::pair<BTreeNode *, BTreeNode *> sibling;
    const int index = getPosFromParent();
    if(index + 1 == capacity + 1){
    }
    return {};
}
