#include "abstract.h"
using namespace std;
class BinarySearchTree: public Tree{
    Node* create(int num){
        Node *n = new Node{num, nullptr, nullptr};
        return n;
    }
    int max(int a, int b){
        if(a > b){
            return a;
        }else{
            return b;
        }
    }
    int depthCounter(Node* n, int num){
        if(num > n->value){
            return 1 + depthCounter(n->right, num);
        }else if(num < n->value){
            return 1 + depthCounter(n->left, num);
        }else{
            return 0;
        }
    }
    Node* mostleft(Node* n){
        Node* current = n;
        while(current->left != nullptr){
            current = current->left;
        }
        return current;
    }
public:
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
    int maxHeight(Node* n){
        if(n == nullptr){
            return 0;
        }else{
            return 1 + max(maxHeight(n->left), maxHeight(n->right));
        }
    }
    int height(Node* n, int num){
        Node* searched = search(n, num);
        if(searched == nullptr){
            return -1;
        }else{
            return maxHeight(searched) - 1;
        }
    }
    
    int depth(Node *n, int num){
        if(search(n, num)){
            return depthCounter(n, num);
        }else{
            return -1;
        }
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
                } else {
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
};
