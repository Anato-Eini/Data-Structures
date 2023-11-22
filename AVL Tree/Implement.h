#include "Abstract.h"
#include <iostream>
using namespace std;
class AVLTree: public Abstract{
    Node* root;
    Node* createNode(int num){
        return new Node{num, 1, nullptr, nullptr};
    }
    int max(int num1, int num2){
        return (num1 > num2) ? num1 : num2;
    }
    int heightNode(Node* node){
        return (!node) ? 0 : node->height;
    }
    Node* rotateLeft(Node* node){
        Node* tempRight = node->right, *tempRightLeft = tempRight->left;
        tempRight->left = node;
        node->right = tempRightLeft;
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        tempRight->height = max(heightNode(tempRight->right), heightNode(tempRight->left)) + 1;
        return tempRight;
    }
    Node* rotateRight(Node* node){
        Node* tempLeft = node->left, *tempLeftRight = tempLeft->right;
        tempLeft->right = node;
        node->left = tempLeftRight;
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        tempLeft->height = max(heightNode(tempLeft->left), heightNode(tempLeft->right)) + 1;
        return tempLeft;
    }
    Node* minimumValue(Node* node){
        Node* curr = node;
        while(curr->left){
            curr = curr->left;
        }
        return curr;
    }
public:
    AVLTree(){
        root = nullptr;
    }
    Node* insertNode(Node* node, int num){
        if(node == nullptr){
            return createNode(num);
        }else if(num >= node->value){
            node->right = insertNode(node->right, num);
        }else if(num < node->value){
            node->left = insertNode(node->left, num);
        }
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        int balanceFactor = heightNode(node->right) - heightNode(node->left);
        if(balanceFactor < -1){
            if(node->left->right){
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }else if(node->left->left)
                return rotateRight(node);
        }else if (balanceFactor > 1){
            if(node->right->left){
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }else if(node->right->right){
                return rotateLeft(node);
            }
        }
        return node;
    }
    Node* deleteNode(Node* node, int num){
        if(!node){
            return nullptr;
        }else if(num < node->value){
            
        }
    }
    Node* searchNode(Node*, int){

    }
    int depth(Node*){

    }
    int height(Node*){

    }
    int maxHeight(Node*){

    }
    void print(){

    }
};