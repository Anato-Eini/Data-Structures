#include "BTreeNode.h"

BTreeNode::BTreeNode(const int & capacity, const bool & isLeaf) : size(0), capacity(capacity - 1),
                                                                  elem(new int[capacity - 1]),
                                                                  children(new BTreeNode*[capacity]), parent(nullptr),
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

BTreeNode* BTreeNode::getChild(const int & key) const
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(elem[i] > key)
            return children[i];
        if(elem[i] == key)
            return nullptr;
    }
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

    if(parentNode->isFull())
        parentNode->splitNode();
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
}

int BTreeNode::removeElem(const int & index) {
    const int element = elem[index];
    for(int i = index + 1; i < size; i++)
        elem[i - 1] = elem[i];
    size--;
    return element;
}

void BTreeNode::mergeContents(const BTreeNode* src, BTreeNode* dest, const int & elementIndex)
{
    int & destSize = dest->size, * destElem = dest->elem;
    BTreeNode ** srcChildren = src->children, ** destChildren = dest->children, * parent = src->parent;
    const int & srcSize = src->size, * srcElem = src->elem;

    const int element = parent->removeElem(elementIndex);

    for(int j = srcSize - 1; j >= 0; j--)
    {
        destElem[j + srcSize + 1] = destElem[j];
        destChildren[j + 1 + srcSize] = destChildren[j + 1];
    }

    destChildren[srcSize + 1] = destChildren[0];
    destElem[srcSize] = element;

    for(int j = 0; j < srcSize; j++)
    {
        destElem[j] = srcElem[j];
        destChildren[j] = srcChildren[j];
    }
    destChildren[srcSize] = srcChildren[srcSize];

    destSize += srcSize;

    if(dest->isFull())
        dest->splitNode();

    if(parent->isEmpty())
        delete parent;

    delete src;
}


void BTreeNode::mergeChild(BTreeNode* node)
{
    const int & parentSize = parent->size;
    BTreeNode ** parentChildren = parent->children;

    //removing of variable node
    if(node->elem[0] < elem[0])
    {
        for(int i = 0; i <= parentSize; i++)
            if(parentChildren[i] == node)
            {
                for(++i; i <= parentSize; i++)
                    parentChildren[i - 1] = parentChildren[i];

                mergeContents(node, this, i);

                break;
            }
    }
    //removing of this node
    else
    {
        for (int i = 0; i <= parentSize; i++)
            if (parentChildren[i] == this)
            {
                for (++i; i <= parentSize; i++)
                    parentChildren[i - 1] = parentChildren[i];

                mergeContents(this, node, i);

                break;
            }
    }

    if(parentSize == 0)
        parent->underFlow();
}

void BTreeNode::underFlow()
{
    if(!parent)
        return;

    const int parentSize = parent->size;
    BTreeNode ** parentChildren = parent->children;

    for (int i = 0; i <= parentSize; i++)
        if (parentChildren[i] == this)
        {
            BTreeNode* sibling;
            bool isLeft;

            if (i + 1 <= parentSize)
            {
                isLeft = false;
                sibling = parentChildren[i + 1];
            } else
            {
                isLeft = true;
                sibling = parentChildren[i - 1];
            }

            if (sibling->size < capacity / 2 && i - 1 >= 0 && !isLeft)
            {
                sibling = parentChildren[i - 1];
                isLeft = true;
            }

            if (sibling->size < capacity / 2)
                mergeChild(sibling);
            else if (isLeft)
            {
                int& parentElement = parent->elem[i - 1];
                insert(parentElement);
                parentElement = sibling->removeElem(sibling->size - 1);
            }
            else
            {
                int& parentElement = parent->elem[0];
                insert(parentElement);
                parentElement = sibling->removeElem(0);
            }
            return;
        }
}


void BTreeNode::deleteKey(const int& key)
{
    for(int i = 0; i < size; i++)
    {
        if(elem[i] == key)
        {
            if(isLeaf)
            {
                for(++i; i < size; i++)
                    elem[i - 1] = elem[i];

                size--;
                if(isEmpty())
                    underFlow();

            } else
            {
                BTreeNode* substitute = getPredecessor(children[i]);
                elem[i] = substitute->removeElem(substitute->size - 1);
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

void BTreeNode::printInorder(std::ostream& os, const BTreeNode *node, int && level)
{
    if(node){
        int i;
        const int & nodeSize = node->size;
        for(i = 0; i < nodeSize; i++){
            printInorder(os, node->children[i], level + 1);
            os << " " << level << "| " << node->elem[i] << " | -" <<
                (node->parent ? std::to_string(node->parent->elem[0]) : " ") << "- ";
        }

        printInorder(os, node->children[i], level + 1);
        os << '\n';
    }
}

bool BTreeNode::keyPresent(const int& key) const
{
    for(int i = 0; i < size; i++)
        if (elem[i] == key)
            return true;

    return false;
}


bool BTreeNode::isEmpty() const {
    return size == 0;
}

void BTreeNode::moveHalf(BTreeNode *node) {
    int i, j;
    int * nodeElem = node->elem;
    BTreeNode ** nodeChildren = node->children;

    for(i = capacity / 2, j = 0; i < size; i++, j++){
        nodeElem[j] = elem[i];
        if(!isLeaf)
        {
            nodeChildren[j] = children[i + 1];
            nodeChildren[j]->parent = node;
        }
    }

    if(!isLeaf)
    {
        nodeChildren[j] = children[i + 1];
        nodeChildren[j]->parent = node;
    }

    node->size = capacity - (size = capacity / 2) - 1;
}

BTreeNode::~BTreeNode(){
    delete[] elem;
    if(!isLeaf)
        for(int i = 0; i < capacity; i++)
            delete children[i];
    delete[] children;
    delete parent;
}

std::ostream &operator<<(std::ostream &os, BTreeNode *node) {
    BTreeNode::printInorder(os, node, 1);
    return os;
}
