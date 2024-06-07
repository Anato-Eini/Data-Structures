#include "Trie.h"

Trie::Trie() : root(new Node{nullptr}) {}

Trie &Trie::insert(const std::string &text)
{
    Node* current = root;
    for(const char & c : text)
    {
        if(!current->node[c - 'a'])
            current->node[c - 'a'] = new Node{current};

        current = current->node[c - 'a'];
    }

    current->endWord = true;

    return *this;
}

bool Trie::search(const std::string &text) const
{
    const Node* current = root;
    for(const char & c : text)
    {
        if(current->node[c - 'a'])
            current = current->node[c - 'a'];
        else
            return false;
    }

    return true;
}

void Trie::print(std::ostream &os, Node *node, std::string &&text)
{
    if(node->endWord)
        os << text + '\n';

    for(int i = 0; i < 26; i++)
        if(node->node[i])
            print(os, node->node[i], text + (char)(i + 'a'));
}
std::ostream & operator<<(std::ostream & os, Trie* tree)
{
    tree->print(os, tree->root, "");
    return os;
}
