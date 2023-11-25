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
    Node* minimumValue(Node* node){
        Node* curr = node;
        while(curr->left)
            curr = curr->left;
        return curr;
    }
    /*
     * These two functions are for rotating nodes ie making parent node A with child node B and C, as a child to either
     * node B or node C
    */
    Node* rotateLeft(Node* node){
        cout << "Rotating node " << node->value << " to the left" << endl;
        Node* tempRight = node->right, *tempRightLeft = tempRight->left;
        tempRight->left = node;
        node->right = tempRightLeft;
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        tempRight->height = max(heightNode(tempRight->right), heightNode(tempRight->left)) + 1;
        return tempRight;
    }
    Node* rotateRight(Node* node){
        cout << "Rotating node " << node->value << " to the right" << endl;
        Node* tempLeft = node->left, *tempLeftRight = tempLeft->right;
        tempLeft->right = node;
        node->left = tempLeftRight;
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        tempLeft->height = max(heightNode(tempLeft->left), heightNode(tempLeft->right)) + 1;
        return tempLeft;
    }
public:
    Node* insertNode(Node* node, int num){
        //We will insert the node the same as we insert a node in Binary Search Tree recursively.
        if(node == nullptr)
            return createNode(num);
        else if(num >= node->value)
            node->right = insertNode(node->right, num);
        else if(num < node->value)
            node->left = insertNode(node->left, num);
        /*
         * Updates the height of each node including its balanceFactor.
         * We will rotate the nodes based on the balanceFactor ie if the balance factor is -1 > then we will rotate
         * either to the right or right and left, else if 1 < then we will rotate to the left or left and right
         * depending on the value inserted.
         */
        node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
        int balanceFactor = heightNode(node->right) - heightNode(node->left);
        if(balanceFactor < -1){
            if(num < node->left->value){
                return rotateRight(node);
            }else if(num > node->left->value){
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }else if (balanceFactor > 1){
            if(num > node->right->value){
                return rotateLeft(node);
            }else if(num < node->right->value){
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }
    Node* deleteNode(Node* node, int num){
        Node *returner = nullptr;
        /*
         * Searches the element recursively down the tree. If found, determine if it has 1 child, children or none.
         * If none, return as nullptr, else if it has 1 child then make it a new child of the parent else if it has more
         * than 1 child then search for the minimum value of its right child, swap the elements, then delete the swapped
         * node.
        */
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

        //I assigned returner as a new child to its parent.
        if(!returner){
            returner = node;
        }
        /*
         * Updates the height of each node including its balanceFactor.
         * We will rotate the nodes based on the balanceFactor ie if the balance factor is -1 > then we will rotate
         * either to the right or right and left, else if 1 < then we will rotate to the left or left and right
         * depending on the value inserted.
         */

        returner->height = max(heightNode(returner->right), heightNode(returner->left)) + 1;
        int balanceFactor = heightNode(returner->right) - heightNode(returner->left);
        if(balanceFactor < -1){
            if(num < node->left->value){
                return rotateRight(node);
            }else if(num > node->left->value){
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }else if (balanceFactor > 1){
            if(num > node->right->value){
                return rotateLeft(node);
            }else if(num < node->right->value){
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return returner;
    }
    Node* searchNode(Node* node, int num){
        /*
         * Similar to how we search a node in insertNode and deleteNode, we will find the correct position of node A
         * by comparing its element to the current node. If the number you're looking for is bigger than the number in
         * the current node, traverse to the right otherwise traverse to the left until you'll hit a nullptr (which
         * means the element did not exist) or a node that matches with the number you're looking for.
        */
        if(!node || node->value == num)
            return node;
        else if(num < node->value)
            return searchNode(node->left, num);
        else
            return searchNode(node->right, num);
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