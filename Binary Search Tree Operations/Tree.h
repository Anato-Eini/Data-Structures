#include "abstract.h"
#include <iostream>
using namespace std;
class BinarySearchTree: public Tree{
    Node* create(int num){
        return new Node{num, nullptr, nullptr};
    }
    int max(int a, int b){
        return (a > b) ? a : b;
    }
    Node* mostleft(Node* n){
        Node* current = n;
        while(current->left != nullptr)
            current = current->left;
        return current;
    }
public:
    /*
     If our element > to current node, traverse to the right child, else if our element < to current node, traverse to left
    child until we reach nullptr then create a new node right after
    */
    Node* insert(Node *n, int num){
        if(n == nullptr)
            return create(num);
        else if(n->value < num)
            n->right = insert(n->right, num);
        else if(n->value > num)
            n->left = insert(n->left, num);
        return n;
    }
    /*
    If our element > to current node, traverse to the right child, else if our element < to current node, traverse to left
    child until we reach nullptr or a node that's equal to our element
    */
    Node* search(Node* n, int num){
        if(!n || n->value == num)
            return n;
        else if(num > n->value)
            return search(n->right, num);
        else
            return search(n->left, num);
    }

    //maximum height of the tree, including the root
    int maxHeight(Node* n){
        if(n == nullptr){
            return 0;
        }else{
            return 1 + max(maxHeight(n->left), maxHeight(n->right));
        }
    }

    //Determine if the element is present, if it returns nullptr, the element is not present in the tree. 
    //Otherwise if found then make it as root and use maxHeight function.
    int height(Node* n, int num){
        Node* searched = search(n, num);
        if(searched == nullptr){
            return -1;
        }else{
            return maxHeight(searched) - 1;
        }
    }


    /*
        Count the nodes it has passed from root down to that number
    */
    int depth(Node *n, int num){
        if(num > n->value){
            return 1 + depth(n->right, num);
        }else if(num < n->value){
            return 1 + depth(n->left, num);
        }else {
            return 0;
        }
    }

    /*
     * Search first for the element the same way we search for an element in a binary search tree.
     * If found, determine the number of children.
     * If 0 children, return nullptr
     * If 1 child, determine if left child or right child is present then return that child;
     * If 2 children, in my own implementation, I search for the smallest element leaf node from the right child,
     * swap the elements to the current node then delete that leaf node
     */
    Node* deleteNode(Node* n, int num) {
        if (n == nullptr) {
            return n;
        }
        Node* returner;
        if (num > n->value) {
            n->right = deleteNode(n->right, num);
        } else if (num < n->value) {
            n->left = deleteNode(n->left, num);
        } else {
            if (n->right != nullptr && n->left != nullptr) {
                Node* minNode = mostleft(n->right);
                n->value = minNode->value;
                n->right = deleteNode(n->right, minNode->value);
            } else {
                if (n->left) {
                    returner = n->left;
                    delete n;
                    return returner;
                } else if (n->right) {
                    returner = n->right;
                    delete n;
                    return returner;
                } else {
                    delete n;
                    return nullptr;
                }
            }
        }
        return n;
    }
    //Pre-order Traversal
    void printPR(Node* node){
        if(node){
            cout << node->value << " ";
            printPR(node->left);
            printPR(node->right);
        }
    }
    //Inorder Traversal
    void printI(Node* node){
        if(node){
            printI(node->left);
            cout << node->value << " ";
            printI(node->right);
        }
    }
    //Post-order Traversal
    void printPO(Node* node){
        if(node){
            printPO(node->left);
            printPO(node->right);
            cout << node->value << " ";
        }
    }
};
