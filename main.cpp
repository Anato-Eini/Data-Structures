
#include <iostream>
using namespace std;

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

Node* create(int num){
    Node *n = new Node{num, nullptr, nullptr};
    return n;
}
Node* insert(Node *n, int num){
    if(n == nullptr)
        return create(num);
    else if(n->value < num)
        n->right = insert(n->right, num);
    else if(n->value > num)
        n->left = insert(n->left, num);
    return n;
}
Node* search(Node* n, int num){
    if(n == nullptr)
        return nullptr;
    else if(num > n->value)
        return search(n->right, num);
    else if(num < n->value)
        return search(n->left, num);
    else return n;
}
Node* mostleft(Node* n){
    Node* current = n;
    while(current->left != nullptr){
        current = current->left;
    }
    return current;
}
void deleteNode(Node*& n, int num) {
    if (n == nullptr) {
        return;
    }
    if (num > n->value) {
        deleteNode(n->right, num);
    } else if (num < n->value) {
        deleteNode(n->left, num);
    } else {
        if (n->right != nullptr && n->left != nullptr) {
            Node* minNode = mostleft(n->right);
            n->value = minNode->value;
            deleteNode(n->right, minNode->value);
        } else {
            Node* temp = n;
            if (n->left != nullptr) {
                n = n->left;
            } else if (n->right != nullptr) {
                n = n->right;
            } else{
                n = nullptr;
            }
            delete temp;
        }
    }
}

void displayTree(struct Node* node) {
    if (node != nullptr) {
        displayTree(node->left);
        cout << node->value << " ";
        displayTree(node->right);
    }
}

int main(void) {
    struct Node* node = nullptr;
    int operation,input;
    do {
        cout << "Enter operation: ";
        cin >> operation;
        switch (operation) {
            case 1:
                cout << "Enter element to add: ";
                cin >> input;
                node = insert(node, input);
                break;
            case 2:
                cout << "Enter element to search: ";
                cin >> input;
                cout << endl;
                if (search(node, input) != nullptr) {
                    cout << input<< " exists" << endl;
                }else {
                    cout << input <<" does not exists" << endl;
                }
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                deleteNode(node, input);
                cout << endl;
                displayTree(node);
                cout << endl;
                break;
            default:
                break;
        }
        cout << endl;
    }while(operation != 0);
    displayTree(node);
}