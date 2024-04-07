#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main() {
    auto* tree = new BinarySearchTree();
    int operation, input, result;
    do {
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
                tree->searchNode(input);
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                tree->deleteNode(input);
                break;
            case 4:
                cout << "Max height of the tree is: " << tree->treeHeight() << '\n';
                break;
            case 5:
                cout << "Enter element: ";
                cin >> input;
                result = tree->heightNode(input);
                cout << "Element " << input << (result == -1 ? " does not exist" : "'s height: " +
                to_string(result)) << '\n';
                break;
            case 6:
                cout << "Enter element: ";
                cin >> input;
                result = tree->depthNode(input);
                cout << "Element " << input << (result < 0 ? " does not exist" : "'s depth: " + to_string(result))
                << '\n';
                break;
            case 7:
                cout << "1-Pre-order Traversal | 2-In-order Traversal | 3-Post-order Traversal |"
                        " 4-Breadth-First Search Traversal | 5-Default: ";
                cin >> input;
                switch (input) {
                    case 1: tree->printPreOrder();
                        break;
                    case 2: tree->printInorder();
                        break;
                    case 3: tree->printPostOrder();
                        break;
                    case 4: tree->printBFS();
                        break;
                    case 5: cout << tree;
                        break;
                    default: cout << "Invalid Operation";
                }
                cout << '\n';
                break;
            case 8:
                cout << "Enter the sibling's of you want to search: ";
                cin >> input;
                tree->sibling(input);
                break;
            default:
                cout << "Invalid Operation\n";
                break;
        }
        cout << endl;
    }while(operation != 0);
}
