/*
 * I implemented the AVL Tree because of the reason that I was amazed at this visualization. I was merely curious until
 * I got the urge to implement it by myself.
 * https://www.youtube.com/watch?v=mGF61O21W-c
 * A little bit complex and "juggly" but that's what makes it so fun and challenging
 */
#include <iostream>
#include "Implement.h"
using namespace std;
int main(){
    auto* avlTree = new AVLTree();
    Node* root = nullptr, *temp;
    int num;
    char input;
    do{
        cout << "Enter an operation: ";
        cin >> input;
        switch (input) {
            case '+':
                cin >> num;
                root = avlTree->insertNode(root, num);
                break;
            case '-':
                cin >> num;
                root = avlTree->deleteNode(root, num);
                break;
            case 'H':
                cout << "Max Height of the tree is: " << avlTree->height(root) << endl;
                break;
            case 'h':
                cin >> num;
                temp = avlTree->searchNode(root, num);
                if(temp)
                    cout << "The height of the node with an element " << num << " is " << avlTree->height(temp) - 1 << endl;
                else
                    cout << "No such element exists" << endl;
                break;
            case 's':
                cin >> num;
                if(avlTree->searchNode(root, num))
                    cout << "Element " << num << " exists" << endl;
                else
                    cout << "Element " << num << " did not exists" << endl;
                break;
            case 'p':
                cout << "Pick Traversal Algorithm (1-Pre-order Traversal | 2-In-order Traversal | 3-Post-order Traversal: ";
                cin >> num;
                switch (num) {
                    case 1: avlTree->printPR(root);
                        break;
                    case 2: avlTree->printI(root);
                        break;
                    case 3: avlTree->printPO(root);
                        break;
                    default: cout << "Invalid Operation";
                }
                cout << endl;
                break;
            case 'd':
                cin >> num;
                if(avlTree->searchNode(root, num))
                    cout << "The depth of the node with an element " << input << " is " << avlTree->depth(root, num) << endl;
                else
                    cout << "Element " << input << " did not exist" << endl;
                break;
            case 'X':
            case 'x':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid Operation" << endl;
        }
    }while(input != 'X' && input != 'x');
    return 0;
}