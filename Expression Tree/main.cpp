#include<iostream>
#include "Stack.h"
using namespace std;
int main(){
    Stack* stack = new StackOp();
    string input;
    TreeNode* root;
    cout << "Enter string: ";
    cin >> input;
    for(char a: input){
        if(a == '+' || a == '-' || a == '/' || a == '*' || a == '%'){
            TreeNode *c = stack->pop(), *b = stack->pop();
            TreeNode* newNode = new TreeNode{a, b, c};
            stack->push(newNode);
        }else{
            TreeNode* newNode = new TreeNode{a, nullptr, nullptr};
            stack->push(newNode);
        }
    }
    root = stack->pop();
    cout << "Output: ";
    stack->printTree(root);
    cout << endl << "Result: " << stack->evaluateTree(root);
    return 0;
}