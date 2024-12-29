//This file will be used for debugging k-d tree
#include "iostream"
#include "Kd_Tree.h"

int main(){
    int kDimension;
    std::cout << "Enter k dimension: ";
    std::cin >> kDimension;

    Kd_Tree * tree = new Kd_Tree(kDimension);

    int inputKey[kDimension];
    char op;

    while(true)
    {
        std::cout << "Enter op: ";
        std::cin >> op;

        switch (op)
        {
            case '+':
                std::cout << "Enter point coordinate: ";
                for(int i = 0; i < kDimension; i++)
                    std::cin >> inputKey[i];

                tree->insertKey(inputKey);
                break;
            case '-':
                std::cout << "Enter point coordinate: ";
                for(int i = 0; i < kDimension; i++)
                    std::cin >> inputKey[i];

                tree->deleteKey(inputKey);
                break;
            case 's':
                std::cout << "Enter point coordinate: ";
                for(int i = 0; i < kDimension; i++)
                    std::cin >> inputKey[i];

                for(int i = 0; i < kDimension; i++)
                    std::cout << inputKey[i] << " ";

                std::cout << (tree->keyExist(inputKey) ? "" : "doesn't ") << "exists\n";
                break;
            case 'p':
                std::cout << tree;
                break;

            default:
                delete tree;
                return 0;
        }
    }
}