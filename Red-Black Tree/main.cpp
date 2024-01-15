#include "RedBlackTree.h"
int main(){
    auto* tree = new RedBlackTree();
    int operation, input, result;
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
                if (tree->search(input))
                    cout << input<< " exists" << endl;
                else
                    cout << input <<" does not exists" << endl;
                break;
//            case 3:
//                cout << "Enter element to delete: ";
//                cin >> input;
//                root = tree->deleteNode(root, input);
//                break;
            case 4:
                cout << "Max height of the tree is: " << tree->treeHeight() << endl;
                break;
            case 5:
                cout << "Enter element: ";
                cin >> input;
                tempNode = tree->search(input);
                if(!tempNode)
                    cout << "Element did not exist" << endl;
                else
                    cout << "The height of the node with the element " << input << " is " <<
                    tree->nodeHeight(tempNode) << endl;
                break;
            case 6:
                cout << "Enter element: ";
                cin >> input;
                tempNode = tree->search(input);
                if(tempNode)
                    cout << "The depth of the node with the element " << input << " is " << tree->nodeDepth(tempNode) <<
                    endl;
                else
                    cout << "Element not found" << endl;
                break;
//            case 7:
//                cout << "Pick Traversal Algorithm (1-Pre-order Traversal | 2-In-order Traversal |
//                3-Post-order Traversal | 4-Breadth-First Search Traversal: ";
//                cin >> input;
//                switch (input) {
//                    case 1: tree->printPR(root);
//                        break;
//                    case 2: tree->printI(root);
//                        break;
//                    case 3: tree->printPO(root);
//                        break;
//                    case 4: tree->printBFS(root);
//                        break;
//                    default: cout << "Invalid Operation";
//                }
//                cout << endl;
//                break;
//            case 8:
//                cout << "Enter the sibling's of you want to search: ";
//                cin >> input;
//                tempNode = tree->search(root, input);
//                if(tempNode){
//                    if(root->value == input)
//                        cout << "There is no sibling of " << input << endl;
//                    else{
//                        tempNode = tree->sibling(root, input);
//                        if(tempNode && root->value != input)
//                            cout << "The sibling of " << input << " is " << tempNode->value << endl;
//                        else
//                            cout << "There is no sibling of " << input << endl;
//                    }
//                }else
//                    cout << input << " does not exists" << endl;
//                break;
            case 9:
                cout << "Enter the element you want to know of its color: ";
                cin >> input;
                tempNode = tree->search(input);
                if(tempNode)
                    cout << "The color of element " << input << " is " << ((tempNode->isBlack) ? "black\n" : "red\n");
                else
                    cout << input << " does not exists\n";
                break;
            case 10:
                cout << "Enter the element you want to know of its parent: ";
                cin >> input;
                tempNode = tree->search(input);
                if(tempNode)
                    cout << "The parent of element " << input << " is " <<
                    (tempNode->parent ? to_string(tempNode->parent->value) + '\n' : "none\n");
                else
                    cout << input << " does not exists\n";
                break;
            case 11:
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