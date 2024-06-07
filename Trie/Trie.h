#ifndef TRIE_H
#define TRIE_H

#include <string>

#include "Node.h"

class Trie final {
    Node* root;

    void print(std::ostream & os, Node* node, std::string && text);

public:

    Trie();

    Trie & insert(const std::string & text);

    [[nodiscard]] bool search(const std::string & text) const;

    friend std::ostream& operator<<(std::ostream & os, Trie* tree);
};

std::ostream& operator<<(std::ostream & os, Trie* tree);

#endif //TRIE_H
