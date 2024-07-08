#include "BTree.h"
#include <iostream>

using namespace std;
int main()
{
    int maxChildCount = 4;
    cout << "Max Element Per Node: ";
    cin >> maxChildCount;
    auto* tree = new BTree(maxChildCount);
    int operation, input, result;

    for(int i = 0; i < 16; i++)
        tree->insert(i);

    do{
        cout << "Enter operation: ";
        cin >> operation;
        switch (operation) {
            case 1:
                cout << "Enter element to add: ";
                cin >> input;
                tree->insert(input);
                break;
            case 2:
                cout << "Enter element to search: ";
                cin >> input;
                cout << endl;
                if(tree->search(input))
                    cout << input << " exists" << endl;
                else
                    cout << input <<" does not exists" << endl;
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                tree->deleteKey(input);
                break;
            case 4:
                cout << "Max height of the tree is: " << tree->height() << endl;
                break;
            case 5:
                cout << "Enter element: ";
                cin >> input;
                result = tree->height(input);
                if(result == -1)
                    cout << input << " does not exist\n";
                else
                    cout << "The height of " << input << " is " << result << '\n';
                break;
            case 6:
                cout << "Enter element: ";
                cin >> input;
                result = tree->depth(input);
                if(result >= 0)
                    cout << "The depth of the node with the element " << input << " is " << result << '\n';
                else
                    cout << "Element not found" << '\n';
                break;
            case 7:
                cout << tree;
                break;
            default:
                cout << "Invalid Operation";
                break;
        }
        cout << '\n';
    } while (operation != 0);
    return 0;
}