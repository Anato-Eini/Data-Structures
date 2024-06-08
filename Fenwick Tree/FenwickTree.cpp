#include "FenwickTree.h"

FenwickTree::FenwickTree(const int & size) : array(new int[size + 1]), size(size + 1)
{
    for(int i = 0; i <= size; i++)
        array[i] = 0;
}

FenwickTree::FenwickTree() : array(nullptr), size(0) {}

void FenwickTree::print(std::ostream& ostream) const
{
    bool isFirst = true;
    ostream << "[ ";
    for(int i = 1; i < size; i++)
    {
        if(!isFirst)
            ostream << ", ";
        else
            isFirst = false;

        ostream << array[i];
    }
    ostream << " ]\n";
}


void FenwickTree::buildArray(const int & size)
{
    if(array)
        clearArray();

    array = new int[size + 1];
    for(int i = 0; i <= size; i++)
        array[i] = 0;

    this->size = size + 1;
}


FenwickTree& FenwickTree::buildTree(const int array[], const int& n)
{
    buildArray(n);

    for(int i = 0; i < n; i++)
        for(int j = i + 1; j <= n; j += j & -j)
            this->array[j] += array[i];

    return *this;
}

FenwickTree& FenwickTree::buildTree(const std::vector<int>& array)
{
    const int size = static_cast<int>(array.size());
    buildArray(size);

    for(int i = 0; i < size; i++)
        for(int j = i + 1; j <= size; j += j & -j)
            this->array[j] += array[i];

    return *this;
}

void FenwickTree::update_tree(int index, int && value) const
{
    for(++index; index < size; index += index & -index)
        array[index] += value;
}

FenwickTree& FenwickTree::updateArray(int array[], const int& index, const int& value)
{
    const int prevValue = array[index];
    array[index] = value;

    update_tree(index, value - prevValue);
    return *this;
}


int FenwickTree::getSum(int index) const
{
    int sum = 0;
    for(++index; index > 0; index -= index & -index)
        sum += array[index];

    return sum;
}

FenwickTree & FenwickTree::clearArray() {
    delete[] array;

    return *this;
}

FenwickTree::~FenwickTree(){
    clearArray();
}

std::ostream & operator<<(std::ostream & ostream, const FenwickTree * tree)
{
    tree->print(ostream);

    return ostream;
}