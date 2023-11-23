#include <iostream>
#include "Implement.h"
using namespace std;
int main(){
    AVLTree* avlTree = new AVLTree();
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
                avlTree->print(root);
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
                cout << "Exiting..." << endl;
                break;
            case 'x':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid Operation" << endl;
        }
    }while(input != 'X' && input != 'x');
    return 0;
}