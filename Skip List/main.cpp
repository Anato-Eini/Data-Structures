#include "iostream"

#include "SkipList.h"

int main()
{
    auto * list = new SkipList(0.5, 3);

    for(int i = 10; i >= 1; i--)
        list->insertKey(i);

    for(int i = 11; i <= 20; i++)
        list->insertKey(i);

    for(int i = 1; i <= 20; i++)
    {
        if(!list->keyExist(i))
            return 1;
    }

    for(int i = 1; i <= 20; i++)
    {
        list->deleteKey(i);
    }

    for(int i = 11; i <= 20; i++)
        list->insertKey(i);

    std::cout << list;

    delete list;
    return 0;
}
