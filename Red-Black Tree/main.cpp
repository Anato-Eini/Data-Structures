#include "RedBlackTree.h"
int main(){
    auto* tree = new RedBlackTree();
    int operation, input;
    Node* tempNode;
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
                if (tree->search(input) != tree->nullNode())
                    cout << input<< " exists" << endl;
                else
                    cout << input <<" does not exists" << endl;
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                tempNode = tree->search(input);
                if(tempNode != tree->nullNode()) {
                    tree->deleteNode(tempNode);
                    cout << tree;
                }else
                    cout << input << " does not exist\n";
                break;
            case 4:
                cout << "Max height of the tree is: " << tree->treeHeight() << endl;
                break;
            case 5:
                cout << "Enter element: ";
                cin >> input;
                tempNode = tree->search(input);
                if(tempNode == tree->nullNode())
                    cout << "Element did not exist" << endl;
                else
                    cout << "The height of the node with the element " << input << " is " <<
                    tree->nodeHeight(tempNode) << endl;
                break;
            case 6:
                cout << "Enter element: ";
                cin >> input;
                tempNode = tree->search(input);
                if(tempNode != tree->nullNode())
                    cout << "The depth of the node with the element " << input << " is " << tree->nodeDepth(tempNode) <<
                    endl;
                else
                    cout << "Element not found" << endl;
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