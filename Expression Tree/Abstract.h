#include "TreeNode.h"
class Stack{
public:
    virtual void push(TreeNode*) = 0;
    virtual TreeNode* pop() = 0;
    virtual void printTree(TreeNode*) = 0;
    virtual int evaluateTree(TreeNode*) = 0;
};