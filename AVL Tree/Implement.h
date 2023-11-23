#include "Abstract.h"
#include <iostream>
using namespace std;
class AVLTree: public Abstract{
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
        cout << "Rotating node " << node->value << " to the left..." << endl;
        Node* tempRight = node->right, *tempRightLeft = tempRight->left;
        tempRight->left = node;
        node->right = tempRightLeft;
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        tempRight->height = max(heightNode(tempRight->right), heightNode(tempRight->left)) + 1;
        return tempRight;
    }
    Node* rotateRight(Node* node){
        cout << "Rotating node " << node->value << " to the right..." << endl;
        Node* tempLeft = node->left, *tempLeftRight = tempLeft->right;
        tempLeft->right = node;
        node->left = tempLeftRight;
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        tempLeft->height = max(heightNode(tempLeft->left), heightNode(tempLeft->right)) + 1;
        return tempLeft;
    }
    Node* minimumValue(Node* node){
        Node* curr = node;
        while(curr->left)
            curr = curr->left;
        return curr;
    }
public:
    Node* insertNode(Node* node, int num){
        if(node == nullptr)
            return createNode(num);
        else if(num >= node->value)
            node->right = insertNode(node->right, num);
        else if(num < node->value)
            node->left = insertNode(node->left, num);

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
        Node *returner = nullptr;
        if(!node)
            return nullptr;
        else if(num < node->value)
            node->left = deleteNode(node->left, num);
        else if(num > node->value)
            node->right = deleteNode(node->right, num);
        else{
            if(node->left && node->right){
                Node* temp = minimumValue(node->right);
                node->value = temp->value;
                node->right = deleteNode(node->right, node->value);
            }else if(node->left)
                returner = node->left;
            else if(node->right)
                returner = node->right;
            else return nullptr;
        }
        if(!returner){
            returner = node;
        }
        returner->height = max(heightNode(returner->right), heightNode(returner->left)) + 1;
        int balanceFactor = heightNode(returner->right) - heightNode(returner->left);
        if (balanceFactor > 1) {
            if (returner->right->left) {
                returner->right = rotateRight(returner->right);
                return rotateLeft(returner);
            } else if (returner->right->right)
                return rotateLeft(returner);
        } else if (balanceFactor < -1) {
            if (returner->left->right) {
                returner->left = rotateLeft(returner->left);
                return rotateRight(returner);
            } else if (returner->left->left)
                return rotateRight(returner);
        }
        return returner;
    }
    Node* searchNode(Node* node, int num){
        if(!node)
            return nullptr;
        else if(num < node->value)
            return searchNode(node->left, num);
        else if(num > node->value)
            return searchNode(node->right, num);
        else return node;
    }
    int depth(Node* node, int num){
        if(num < node->value)
            return 1 + depth(node->left, num);
        else if(num > node->value)
            return 1 + depth(node->right, num);
        else return 0;
    }
    int height(Node* node){
        return max(heightNode(node->left), heightNode(node->right)) + 1;
    }
    void print(Node* node){
        if(node){
            print(node->left);
            cout << node->value << " ";
            print(node->right);
        }
    }
};