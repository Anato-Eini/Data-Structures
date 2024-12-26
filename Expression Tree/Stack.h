#include "Abstract.h"
#include <iostream>
using namespace std;
class StackOp: public Stack{
    TreeNode* head; // hello my sentinel

    //check if empty
    bool isEmpty(){
        return head->next == nullptr;
    }

    //self-explanatory nani diri nga part
    int evaluate(int number1, char op, int number2){
        switch (op) {
            case '+':
                return number1 + number2;
            case '-':
                return number1 - number2;
            case '%':
                return number1 % number2;
            case '/':
                return number1 / number2;
            case '*':
                return number1 * number2;
        }
        return 0;
    }
public:
    //constructor
    StackOp(){
        head->next = nullptr;
    }

    //create node first then point its next to the next of head since we're using sentinel
    void push(TreeNode* newNode){
        newNode->next = head->next;
        head->next = newNode;
    }

    //we're dealing with nodes in a tree, we'll just return the node to reuse its address pointer
    TreeNode* pop(){
        if(!isEmpty()){
            TreeNode* out = head->next;
            head->next = head->next->next;
            return out;
        }else{
            cout << "Stack's Empty" << endl;
            return nullptr;
        }
    }

    //printing tree from root to its leaves using inorder traversal
    void printTree(TreeNode* n){
        if(n != nullptr){
            printTree(n->left);
            cout << n->value << " ";
            printTree(n->right);
        }
    }

    //evaluate tree 
    //explanation: if current node contains a number then return that number, otherwise, go to the left child and right child
    int evaluateTree(TreeNode* n){
        if(isdigit(n->value)){
            return atoi(&n->value);//atoi -> character to integer from #include<string>
        }else{
            return evaluate(evaluateTree(n->left), n->value, evaluateTree(n->right));
        }
    }
};
