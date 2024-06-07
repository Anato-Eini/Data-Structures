#ifndef TRIE_H
#define TRIE_H
#include <string>


class Trie final {
struct Node
{
    Node ** node;
    Node * parent;
    bool endWord;

    explicit Node(Node* parent) : node(new Node*[26]), parent(parent), endWord(false)
    {
        for (int i = 0; i < 26; ++i)
        {
            node[i] = nullptr;
        }
    }
};

    Node* root;

public:

    Trie() : root(new Node{nullptr}) {}

    Trie & insert(const std::string & text)
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

    [[nodiscard]] bool search(const std::string & text) const
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

    friend std::ostream& operator<<(std::ostream & os, Trie* tree);
};

std::ostream& operator<<(std::ostream & os, Trie* tree)
{

}

#endif //TRIE_H
