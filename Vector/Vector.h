#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>

template <typename Object>

class Vector{
public:
    explicit Vector(size_t const init_size = 0) : theSize(init_size), theCapacity(init_size + SPARE_CAPACITY)
    , object_(new Object[theCapacity]){}

    Vector(const Vector & rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), object_(new Object[theCapacity])
    {
        for(size_t i = 0; i < theSize; i++)
            object_[i] = rhs.object_[i];
    }

    Vector & operator=(const Vector & rhs)
    {
        if(this != &rhs)
        {
            Vector copy{rhs};
            std::swap(*this, copy);
        }
        return *this;
    }

    ~Vector()
    {
        delete[] object_;
    }

    Vector(Vector && rhs) noexcept : theSize(rhs.theSize), theCapacity(rhs.theCapacity), object_(rhs.object_)
    {
        rhs.object_ = nullptr;
        rhs.theSize = rhs.theCapacity = 0;
    }

    Vector & operator=(Vector && rhs) noexcept
    {
        std::swap(rhs.theCapacity, theCapacity);
        std::swap(rhs.theSize, theSize);
        std::swap(rhs.object_, object_);
        return *this;
    }

    void resize(const size_t newSize)
    {
        if(newSize > theCapacity)
            reserve(newSize * 2);

        theSize = newSize;
    }

    void reserve(const size_t newCapacity)
    {
        if(newCapacity < theSize)
            return;

        auto* newArray = new Object[newCapacity];
        for(size_t i = 0; i < theSize; i++)
            newArray[i] = std::move(object_[i]);

        theCapacity = newCapacity;
        std::swap(object_, newArray);
        delete[] newArray;
    }

    Object & operator[](size_t index)
    {
        return object_[index];
    }

    const Object & operator[](size_t index) const
    {
        return object_[index];
    }

    [[nodiscard]] bool empty() const
    {
        return size() == 0;
    }

    [[nodiscard]] size_t size() const
    {
        return theSize;
    }

    [[nodiscard]] size_t capacity() const
    {
        return theCapacity;
    }

    void push_back(const Object & x)
    {
        if(theSize == theCapacity)
            reserve(2 * theCapacity + 1);

        object_[theSize++] = x;
    }

    void push_back(Object && x)
    {
        if(theSize == theCapacity)
            reserve(2 * theCapacity + 1);

        object_[theSize++] = std::move(x);
    }

    void pop_back()
    {
        --theSize;
    }

    const Object & back() const
    {
       return object_[theSize - 1];
    }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin()
    {
        return &object_[0];
    }

    const_iterator begin() const
    {
        return &object_[0];
    }

    iterator end()
    {
        return &object_[size()];
    }

    const_iterator end() const
    {
        return &object_[size()];
    }

    static constexpr int SPARE_CAPACITY = 16;

private:
    size_t theSize{};
    size_t theCapacity{};
    Object* object_;
};


#endif //VECTOR_H