#include <iostream>
#include "Trie.h"

int main(){
    Trie* trie = new Trie{};
    char choice;
    std::string input;
    while(true){
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch (choice) {
            case 'i':
                std::cin >> input;
                trie->insert(input);
                break;
            case 's':
                std::cin >> input;
                std::cout << input << (trie->search(input) ? "" : " doesn't" ) << " exists\n";
                break;
            case 'p':
                std::cout << trie;
                break;
            case 'x':
                delete trie;
                return 0;
        }
    }
}