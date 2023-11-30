#include "Queue.h"
#include <iostream>
using namespace std;
class BinarySearchTree: public Tree{
    static Node* create(int num){
        return new Node{num, nullptr, nullptr};
    }
    static int max(int a, int b){
        return (a > b) ? a : b;
    }
    static Node* mostleft(Node* node){
        Node* current = node;
        while(current->left)
            current = current->left;
        return current;
    }
public:
    /*
     If our element > to current node, traverse to the right child, else if our element < to current node, traverse to left
    child until we reach nullptr then create a new node right after
    */
    Node* insert(Node *n, int num) override{
        if(!n)
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
    Node* search(Node* node, int num) override{
        if(!node || node->value == num)
            return node;
        else if(num > node->value)
            return search(node->right, num);
        else
            return search(node->left, num);
    }

    //maximum height of the tree, including the root
    int maxHeight(Node* node) override{
        if(!node)
            return 0;
        else
            return 1 + max(maxHeight(node->left), maxHeight(node->right));
    }
    //Determine if the element is present, if it returns nullptr, the element is not present in the tree. 
    //Otherwise if found then make it as root and use maxHeight function.
    int height(Node* node, int num) override{
        Node* searched = search(node, num);
        if(!searched)
            return -1;
        else
            return maxHeight(searched) - 1;
    }
    /*
        Count the nodes it has passed from root down to that number
    */
    int depth(Node *node, int num) override{
        if(num > node->value)
            return 1 + depth(node->right, num);
        else if(num < node->value)
            return 1 + depth(node->left, num);
        else
            return 0;
    }
    Node* sibling(Node* node, int num) override{
        if(node->left && node->left->value == num)
            return node->right;
        else if(node->right && node->right->value == num)
            return node->left;
        else if(node->value > num)
            return sibling(node->left, num);
        else
            return sibling(node->right, num);
    }
    /*
     * Search first for the element the same way we search for an element in a binary search tree.
     * If found, determine the number of children.
     * If 0 children, return nullptr
     * If 1 child, determine if left child or right child is present then return that child;
     * If 2 children, in my own implementation, I search for the smallest element leaf node from the right child,
     * swap the elements to the current node then delete that leaf node
     */
    Node* deleteNode(Node* node, int num) override {
        if (!node)
            return node;
        Node* returner;
        if (num > node->value)
            node->right = deleteNode(node->right, num);
        else if (num < node->value)
            node->left = deleteNode(node->left, num);
        else if (node->right && node->left) {
                Node* minNode = mostleft(node->right);
                node->value = minNode->value;
                node->right = deleteNode(node->right, minNode->value);
        } else if (node->left) {
            returner = node->left;
            delete node;
            return returner;
        } else if (node->right) {
            returner = node->right;
            delete node;
            return returner;
        } else {
            delete node;
            return nullptr;
        }
        return node;
    }
    //Pre-order Traversal
    void printPR(Node* node) override{
        if(node){
            cout << node->value << " ";
            printPR(node->left);
            printPR(node->right);
        }
    }
    //Inorder Traversal
    void printI(Node* node) override{
        if(node){
            printI(node->left);
            cout << node->value << " ";
            printI(node->right);
        }
    }
    //Post-order Traversal
    void printPO(Node* node) override{
        if(node){
            printPO(node->left);
            printPO(node->right);
            cout << node->value << " ";
        }
    }
    //Breadth-first search traversal
    void printBFS(Node* root) override{
        Queue* queue = new QueueList();
        queue->enqueue(root);
        while(!queue->isEmpty()){
            Node* dequeued = queue->dequeue();
            if(dequeued->left)
                queue->enqueue(dequeued->left);
            if(dequeued->right)
                queue->enqueue(dequeued->right);
            cout << dequeued->value << " ";
        }
    }
};
