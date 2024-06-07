#include "SegmentTree.h"

SegmentTree::SegmentTree() : root{nullptr} {}

Node* SegmentTree::generateTreeHelper(int array[], const int left, const int right)
{
    if(left > right)
        return nullptr;

    if(left == right)
        return new Node{array[left], nullptr, nullptr};

    const int middle = (right + left) / 2;

    auto* newNode = new Node{0, generateTreeHelper(array, left, middle),
        generateTreeHelper(array, middle + 1, right)};

    newNode->value = newNode->left->value + newNode->right->value;

    return newNode;
}


SegmentTree& SegmentTree::generateTree(int array[], const int & n)
{
    if(root)
        clearTree();

    root = generateTreeHelper(array, 0, n - 1);

    size = n;
    return *this;
}

Node* SegmentTree::generateTreeHelper(std::vector<int>& array, const int left, const int right)
{
    if(left > right)
        return nullptr;

    if(left == right)
        return new Node{array[left], nullptr, nullptr};

    const int middle = (right + left) / 2;

    auto* newNode = new Node{0, generateTreeHelper(array, left, middle),
        generateTreeHelper(array, middle + 1, right)};

    newNode->value = newNode->left->value + newNode->right->value;

    return newNode;
}

SegmentTree& SegmentTree::generateTree(std::vector<int> & array)
{
    if(root)
        clearTree();

    root = generateTreeHelper(array, 0, static_cast<int>(array.size()));

    size = static_cast<int>(array.size());
    return *this;
}


void SegmentTree::clearTreeHelper(const Node* node)
{
    if(node)
    {
        clearTreeHelper(node->left);
        clearTreeHelper(node->right);
        delete node;
    }
}


SegmentTree & SegmentTree::clearTree()
{
    clearTreeHelper(root);
    return *this;
}

int SegmentTree::queryHelper(
    const Node* node, const int & left, const int & right, const int rangeLeft, const int rangeRight)
{
    if(left <= rangeLeft && right >= rangeRight)
        return node->value;
    if(left > rangeRight || right < rangeLeft)
        return 0;

    const int middle = (rangeLeft + rangeRight) / 2;

    return queryHelper(node->left, left, right, rangeLeft, middle) +
        queryHelper(node->right, left, right, middle + 1, rangeRight);
}


int SegmentTree::query(const int & left, const int & right) const
{
    if(left < 0 || right >= size)
        std::__throw_out_of_range("Out of range");

    return queryHelper(root, left, right, 0, size - 1);
}


void SegmentTree::print(std::ostream& ostream, const bool isLeft, std::string string, const Node* node)
{
    if(!node)
        return;

    string += (isLeft ? "|   " : "    ");
    print(ostream, false, string, node->right);
    ostream << string;
    ostream << (isLeft ? "L----" : "R----");
    ostream << node->value << '\n';
    print(ostream, true, string, node->left);
}

SegmentTree::~SegmentTree()
{
    clearTree();
}


std::ostream & operator<<(std::ostream & ostream, const SegmentTree* tree)
{
    SegmentTree::print(ostream, false, "", tree->root);
    return ostream;
}