#include "iostream"

#include "SkipList.h"

int main()
{
    float rLimit;
    int maxLevel;
    int inputKey;
    char op = '\0';

    std::cout << "Enter randomizer limit: ";
    std::cin >> rLimit;

    std::cout << "Enter max level: ";
    std::cin >> maxLevel;

    auto * list = new SkipList(rLimit, maxLevel);

    while(true)
    {
        std::cout << "Enter op: ";
        std::cin >> op;

        switch (op)
        {
        case '+':
            std::cin >> inputKey;
            list->insertKey(inputKey);
            break;
        case '-':
            std::cin >> inputKey;
            list->deleteKey(inputKey);
            break;
        case 's':
            std::cin >> inputKey;
            std::cout << inputKey << (list->keyExist(inputKey) ? "" : " doesn't") << " exists\n";
            break;
        case 'p':
            std::cout << list;
            break;

            default:
                delete list;
                return 0;
        }
    }
}
