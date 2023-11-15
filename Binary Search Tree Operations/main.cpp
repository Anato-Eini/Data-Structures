#include <iostream>
#include "Tree.h"
using namespace std;
int main() {
    Tree* tree = new BinarySearchTree();
    Node* root = nullptr, *tempNode;
    int operation, input, temp;
    do {
        cout << "Enter operation: ";
        cin >> operation;
        switch (operation) {
            case 1:
                cout << "Enter element to add: ";
                cin >> input;
                root = tree->insert(root, input);
                break;
            case 2:
                cout << "Enter element to search: ";
                cin >> input;
                cout << endl;
                if (tree->search(root, input) != nullptr) {
                    cout << input<< " exists" << endl;
                }else {
                    cout << input <<" does not exists" << endl;
                }
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                tree->deleteNode(root, input);
                cout << endl;
                tree->displayTree(root);
                cout << endl;
                break;
            case 4:
                cout << "Max height of the tree is: " << tree->maxHeight(root) << endl;
                break;
            case 5:
                cout << "Enter element: ";
                cin >> input;
                temp = tree->height(root, input);
                if(temp == -1){
                    cout << "Element did not exist" << endl;
                }else{
                    cout << "The height of the node with the element " << input << " is " << tree->height(root, input) << endl;
                }
                break;
            case 6:
                cout << "Enter element: ";
                cin >> input;
                tempNode = tree->search(root, input);
                if(tempNode != nullptr){
                    cout << "The depth of the node with the element " << input << " is " << tree->depth(root, input) << endl;
                }else{
                    cout << "Element not found" << endl;
                }
                break;
            case 7:
                tree->displayTree(root);
                cout << endl;
                break;
            default:
                cout << "Invalid operation";
                break;
        }
        cout << endl;
    }while(operation != 0);
    tree->displayTree(root);
}
