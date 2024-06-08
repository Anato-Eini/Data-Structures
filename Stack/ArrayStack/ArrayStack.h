#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "vector"

#include "../AbstractStack.h"

template <typename Object>
class ArrayStack final : public AbstractStack<Object>
{
   std::pmr::vector<Object> vector_;

    size_t index;
public:

    ArrayStack();

    void push(Object&& object) override;

    void push(Object& object) override;

    Object& pop() override;

    Object& peek() override;

    [[nodiscard]] bool isEmpty() override;

    [[nodiscard]] size_t size() override;

    ~ArrayStack() override = default;
};

#include "ArrayStack.cpp"

#endif //ARRAYSTACK_H
