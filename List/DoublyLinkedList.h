#ifndef LIST_H
#define LIST_H

#include <algorithm>

#include "Exception.h"
#include "Node.h"
#include "Iterator.h"

template <typename Object>
class DoublyLinkedList
{
public:
    DoublyLinkedList() : head(new Node<Object>), tail(new Node<Object>)
    {
        head->next = tail;
        tail->prev = head;
    }

    DoublyLinkedList(const DoublyLinkedList & rhs)
    {
        this();
        for (auto & x : rhs)
            push_back(x);
    }

    ~DoublyLinkedList()
    {
        clear();
        delete head;
        delete tail;
    }

    DoublyLinkedList & operator=(const DoublyLinkedList & rhs)
    {
        if(this != rhs)
        {
            DoublyLinkedList copy = rhs;
            std::swap(*this, copy);
        }
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList && rhs)  noexcept : theSize(rhs.theSize), head(rhs.head), tail(rhs.tail)
    {
        rhs.theSize = 0;
        rhs.tail = nullptr;
        rhs.head = nullptr;
    }

    DoublyLinkedList & operator=(DoublyLinkedList && rhs) noexcept
    {
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        std::swap(theSize, rhs.theSize);

        return *this;
    }

    iterator begin()
    {
        return {*this, head->next};
    }

    const_iterator begin() const
    {
        const_iterator itr{*this, head};
        return ++itr;
    }

    iterator end()
    {
        return {*this, tail};
    }

    const_iterator end() const
    {
        return {*this, tail};
    }

    [[nodiscard]]size_t size() const
    {
        return theSize;
    }

    [[nodiscard]] bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        while(!empty())
            pop_front();
    }

    Object & front()
    {
        return *begin();
    }

    const Object & front() const
    {
        return *begin();
    }

    Object & back()
    {
        return *--end();
    }

    Object & back() const
    {
        return *--end();
    }

    void push_front(const Object & x)
    {
        insert(begin(), x);
    }

    void push_front(Object && x)
    {
        insert(begin(), std::move(x));
    }

    void push_back(const Object & x)
    {
        insert(end(), x);
    }

    void push_back(Object && x)
    {
        insert(end(), std::move(x));
    }

    void pop_front()
    {
        erase(begin());
    }

    void pop_back()
    {
        erase(--end());
    }

    iterator insert(iterator itr, const Object & x)
    {
        itr.assertIsValid();
        if(itr.theList != this)
            throw IteratorMismatchException{};

        Node * p = itr.current;
        theSize++;
        return {*this, p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    iterator insert(iterator itr, const Object && x)
    {
        Node * p = itr.current;
        theSize++;
        return {*this, p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }

    iterator erase(iterator itr)
    {
        Node* p = itr.current;
        iterator retVal{*this, p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;

        return retVal;
    }

    iterator erase(iterator from, iterator to)
    {
        for(iterator itr = from; from != to; )
            itr = erase(itr);

        return to;
    }
private:
    size_t theSize{};
    Node* head;
    Node* tail;

    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#endif //LIST_H
