#ifndef LIST_H
#define LIST_H

#include <algorithm>

#include "Exception.h"

template <typename Object>
class List
{
    struct Node
    {
        Object data;
        Node *prev;
        Node *next;

        explicit Node(const Object & d = Object{}, Node * p = nullptr, Node *n = nullptr) : data(d), prev(p), next(n) {}

        explicit Node(Object && d, Node * p = nullptr, Node * n = nullptr) : data(d), prev(p), next(n) {}
    };

public:

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
        Node* current;
        const List * theList;

        Object & retrive() const
        {
            return current->data;
        }

        explicit const_iterator(const List & lst, Node* p) : current(p), theList(&lst){}

        void assertIsValid() const
        {
            if(theList == nullptr || current == nullptr || current == theList->head )
                throw IteratorOutOfBoundsException{"Out Of Bounds"};
        }

        friend class List;
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

       explicit iterator(const List & list, Node * p) : const_iterator(list, p){}

       friend class List;
   };

    List() : head(new Node), tail(new Node)
    {
        head->next = tail;
        tail->prev = head;
    }

    List(const List & rhs)
    {
        this();
        for (auto & x : rhs)
            push_back(x);
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }

    List & operator=(const List & rhs)
    {
        if(this != rhs)
        {
            List copy = rhs;
            std::swap(*this, copy);
        }
        return *this;
    }

    List(List && rhs)  noexcept : theSize(rhs.theSize), head(rhs.head), tail(rhs.tail)
    {
        rhs.theSize = 0;
        rhs.tail = nullptr;
        rhs.head = nullptr;
    }

    List & operator=(List && rhs) noexcept
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
