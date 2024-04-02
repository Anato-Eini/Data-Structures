// Deleting a key from a B-tree in C++

#include "BTree.h"
int main() {

    BTree t(3);
    t.insertion(8);
    t.insertion(9);
    t.insertion(10);
    t.insertion(11);
    t.insertion(15);
    t.insertion(16);
    t.insertion(17);
    t.insertion(18);
    t.insertion(20);
    t.insertion(23);

    cout << "The B-tree is: ";
    t.traverse();

    t.deletion(20);

    cout << "\nThe B-tree is: ";
    t.traverse();
}