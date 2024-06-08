#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.h"

class DoublyLinkedList;

template <typename Object>
class const_iterator
{
public:
    const_iterator() : current(nullptr), theList(nullptr) {}

    const Object & operator*() const
    {
        return retrive();
    }

    const_iterator & operator++()
    {
        current = current->next;
        return *this;
    }

    const_iterator operator++(int)
    {
        const_iterator old = *this;
        ++*this;
        return old;
    }

    bool operator==(const const_iterator& rhs) const
    {
        return current == rhs.current;
    }

    bool operator!=(const const_iterator & rhs) const
    {
        return *this != rhs;
    }

protected:
    Node<Object>* current{};
    const DoublyLinkedList * theList{};

    Object & retrive() const
    {
        return current->data;
    }

    explicit const_iterator(const DoublyLinkedList & lst, Node<Object>* p) : current(p), theList(&lst){}

    void assertIsValid() const
    {
        if(theList == nullptr || current == nullptr || current == theList->head )
            throw IteratorOutOfBoundsException{"Out Of Bounds"};
    }

    friend class DoublyLinkedList;
};

class iterator : public const_iterator
{
public:
   iterator() = default;

   Object & operator*()
   {
       return const_iterator::retrive();
   }

   const Object & operator*() const
   {
       return const_iterator::operator*();
   }

   iterator & operator++()
   {
       this->current = this->current->next;
       return *this;
   }

   iterator operator++(int)
   {
       iterator old = *this;
       ++*this;
       return old;
   }

protected:
   explicit iterator(Node* p) : const_iterator(p){}

   explicit iterator(const DoublyLinkedList & list, Node * p) : const_iterator(list, p){}

   friend class DoublyLinkedList;
};

#endif //ITERATOR_H
