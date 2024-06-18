#include "BTreeNode.h"

#include <pstl/execution_defs.h>

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
    children[i + 1] = newChild;
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

void BTreeNode::mergeChild(BTreeNode* node)
{
    const int parentSize = parent->size;
    int element;
    if(node->elem[0] < elem[0])
    {
        for (int i = 0, indexOfElem; i < parentSize; i++)
        {
            if(parent->children[i] == node)
            {
                indexOfElem = i;
                for(i++; i <= parentSize; i++)
                    parent->children[i - 1] = parent->children[i];

                element = parent->removeElem(indexOfElem);
            }
        }
    }else
    {

    }
}

void BTreeNode::underFlow()
{
    if(isLeaf && parent)
    {
       const int size = parent->size;
       for(int i = 0; i <= size; i++)
           if(parent->children[i] == this)
           {
               BTreeNode* sibling = nullptr;
               if(i + 1 <= size)
                   sibling = getPredecessor(parent->children[i + 1]);
               if(sibling && sibling->size < capacity / 2 && i - 1 >= 0)
                   sibling = getSuccessor(parent->children[i - 1]);

               if(sibling->size < capacity / 2)
                   mergeChild(sibling);

               return;
           }
    }else
    {

    }
}


void BTreeNode::deleteKey(const int& key)
{
    for(int i = 0; i < size; i++)
    {
        if(elem[i] == key)
        {
            for(int j = i + 1; j < size; j++)
                elem[j - 1] = elem[j];

            if(isLeaf)
            {
                if(size < capacity / 2)
                {

                }
            }else
            {

            }

            return;
        }
    }
}

BTreeNode* BTreeNode::getSuccessor(BTreeNode* node)
{
    while (node->children[0])
        node = node->children[0];

    return node;
}

BTreeNode* BTreeNode::getPredecessor(BTreeNode* node)
{
    while(node->children[node->size])
        node = node->children[node->size];

    return node;
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

void BTreeNode::printInorder(std::ostream& os, const BTreeNode *node) {
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
    children[i] = nullptr;
    node->size = capacity - (capacity / 2) - 1;
    size = capacity / 2;
}

BTreeNode::~BTreeNode(){
    delete[] elem;
    if(!isLeaf){
        for(int i = 0; i < capacity; i++){
            delete children[i];
        }
    }
    delete[] children;
}

std::ostream &operator<<(std::ostream &os, const BTreeNode *node) {
    BTreeNode::printInorder(os, node);
    return os;
}
