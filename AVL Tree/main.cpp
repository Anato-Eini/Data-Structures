/*
 * I implemented the AVL Tree because of the reason that I was amazed at this visualization. I was merely curious until
 * I got the urge to implement it by myself.
 * https://www.youtube.com/watch?v=mGF61O21W-c
 * A little bit complex and "juggly" but that's what makes it so fun and challenging
 */
#include <iostream>
#include "AVLTree.h"
using namespace std;
int main(){
    auto* avlTree = new AVLTree();
    int num, result;
    char input;
    do{
        cout << "Enter an operation: ";
        cin >> input;
        switch (input) {
            case '+':
                cin >> num;
                avlTree->insertNode(num);
                break;
            case '-':
                cin >> num;
                avlTree->deleteNode(num);
                break;
            case 'H':
                cout << "Max Height of the tree is: " << avlTree->treeHeight() << endl;
                break;
            case 'h':
                cin >> num;
                result = avlTree->height(num);
                cout << num << ((result == -1) ? " not found\n": "\'s height is " + to_string(result)) << '\n';
                break;
            case 's':
                cin >> num;
                cout << "Element " << num << (avlTree->searchNode(num) ? " exists" : " did not exists") << '\n';
                break;
            case 'p':
                avlTree->printTree();
                cout << '\n';
                break;
            case 'd':
                cin >> num;
                result = avlTree->depth(num);
                cout << (result == -1 ? "Element " + to_string(num) + " did not exist": "The depth of the node " +
                        to_string(num) + " is " + to_string(result - 1)) << '\n';
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