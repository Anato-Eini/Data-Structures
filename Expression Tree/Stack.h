#include "Abstract.h"
#include <string>
#include <iostream>
using namespace std;
class StackOp: public Stack{
    TreeNode* head;
    bool isEmpty(){
        return head->next == nullptr;
    }
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
    }
public:
    StackOp(){
        head->next = nullptr;
    }
    void push(TreeNode* newNode){
        newNode->next = head->next;
        head->next = newNode;
    }
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
    void printTree(TreeNode* n){
        if(n != nullptr){
            printTree(n->left);
            cout << n->value << " ";
            printTree(n->right);
        }
    }
    int evaluateTree(TreeNode* n){
        if(isdigit(n->value)){
            return atoi(&n->value);
        }else{
            return evaluate(evaluateTree(n->left), n->value, evaluateTree(n->right));
        }
    }
};