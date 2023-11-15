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
        /*
        Explanation: If ang current value is an operator, create new node -> pop the stack twice and make it the left child
        and right child respectively of the new node and push it back to stack, otherwise if number, then create new Node assign
        nullpointers to its children and push it back to stack
        */
        if(a == '+' || a == '-' || a == '/' || a == '*' || a == '%'){
            TreeNode *c = stack->pop(), *b = stack->pop();
            if(c == nullptr || b == nullptr){
                return 0; // Check if Invalid Expression
            }
            TreeNode* newNode = new TreeNode{a, b, c};
            stack->push(newNode);
        }else{
            TreeNode* newNode = new TreeNode{a, nullptr, nullptr};
            stack->push(newNode);
        }
    }
    //The last value from stack will be automatically be a root to the tree
    root = stack->pop();
    cout << "Output: ";
    stack->printTree(root);
    cout << endl << "Result: " << stack->evaluateTree(root);
    return 0;
}
