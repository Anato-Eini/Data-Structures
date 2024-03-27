#include "SplayTree.h"
int main()
{
    auto* tree = new SplayTree();
    int operation, input, result;
    for(int i = 1; i <= 10; i++){
        tree->insertNode(i);
        tree->insertNode(21 - i);
    }
    do{
        cout << "Enter operation: ";
        cin >> operation;
        switch (operation) {
            case 1:
                cout << "Enter element to add: ";
                cin >> input;
                tree->insertNode(input);
                break;
            case 2:
                cout << "Enter element to search: ";
                cin >> input;
                cout << endl;
                if (tree->search(input)->value == input)
                    cout << input << " exists" << endl;
                else
                    cout << input <<" does not exists" << endl;
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                tree->deleteNode(input);
                break;
            case 4:
                cout << "Max height of the tree is: " << tree->treeHeight() << endl;
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
                tree->printTree();
                break;
            default:
                cout << "Invalid Operation";
                break;
        }
        cout << '\n';
    } while (operation != 0);
    return 0;
}
