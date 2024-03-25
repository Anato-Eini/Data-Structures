#include "SplayTree.h"
int main()
{
    SplayTree* splayTree = new SplayTree{};
    splayTree->setRoot(new Node{100, nullptr, nullptr, nullptr});
    splayTree->getRoot()->left = new Node{50, nullptr, nullptr, nullptr};
    splayTree->getRoot()->left->left = new Node{20, nullptr, nullptr, nullptr};
    splayTree->printTree();
    splayTree->search(20);
    cout << "Preorder traversal of the modified Splay tree is \n";
    splayTree->printTree();
    return 0;
}

// This code is contributed by rathbhupendra
