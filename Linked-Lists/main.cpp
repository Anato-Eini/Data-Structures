#include<iostream>
#include "Implement.h"
using namespace std;
int main(){
    DoublyList* list = new DoublyLinkedList();
    int size, input;
    cout << "Enter size of linked list: ";
    cin >> size;
    for(int a = 1; a <= size; a++){
        cout << "Enter element " << a << ": ";
        cin >> input;
        list->addFirst(input);
    }
    cout << "Original list: ";
    list->print();
    if(list->isPalindrome()) cout << "The linked list is a palindrome.";
    else cout << "The linked list is not a palindrome.";
    return 0;
}