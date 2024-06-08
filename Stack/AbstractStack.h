#ifndef ABSTRACTSTACK_H
#define ABSTRACTSTACK_H

template <typename Object>
class AbstractStack
{
public:
    virtual void push(Object && object) = 0;

    virtual void push(Object & object) = 0;

    virtual Object & pop() = 0;

    virtual Object & peek() = 0;
};

#endif //ABSTRACTSTACK_H