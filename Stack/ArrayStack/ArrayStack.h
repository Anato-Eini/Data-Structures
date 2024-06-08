#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "vector"

#include "../AbstractStack.h"

template <typename Object>
class ArrayStack final : public AbstractStack<Object>
{
   std::pmr::vector<Object> vector_;
public:
    void push(Object&& object) override;

    void push(Object& object) override;

    Object& pop() override;

    Object& peek() override;

};



#endif //ARRAYSTACK_H
