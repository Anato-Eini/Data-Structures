#include "iostream"

#include "SkipList.h"

int main(int argc, char* argv[])
{
    auto * list = new SkipList(1, 3);

    for(int i = 10; i >= 1; i--)
        list->insertKey(i);

    for(int i = 11; i <= 20; i++)
        list->insertKey(i);

    std::cout << list;

    delete list;
    return 0;
}
