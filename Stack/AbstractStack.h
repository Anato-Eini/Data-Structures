#ifndef ABSTRACTSTACK_H
#define ABSTRACTSTACK_H

#include "cstddef"

template <typename Object>
class AbstractStack
{
public:
    virtual void push(Object && object) = 0;

    virtual void push(Object & object) = 0;

    virtual Object & pop() = 0;

    virtual Object & peek() = 0;

    virtual bool isEmpty() = 0;

    virtual size_t size() = 0;

    virtual ~AbstractStack() = default;
};

#endif //ABSTRACTSTACK_H