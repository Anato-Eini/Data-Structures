#ifndef DATA_STRUCTURES_NODE_H
#define DATA_STRUCTURES_NODE_H

struct Node
{
    Node ** node;
    Node * parent;
    bool endWord;

    explicit Node(Node* parent) : node(new Node*[26]), parent(parent), endWord(false)
    {
        for (int i = 0; i < 26; ++i)
            node[i] = nullptr;
    }
};

#endif //DATA_STRUCTURES_NODE_H
