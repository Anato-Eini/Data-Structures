#ifndef ITERATOROUTOFBOUNDSEXCEPTION_H
#define ITERATOROUTOFBOUNDSEXCEPTION_H

#include "exception"
#include "string"

class IteratorOutOfBoundsException : public std::exception
{
    std::string message;
public:
    explicit IteratorOutOfBoundsException(std::string& message) : message(std::move(message)) {}

    explicit IteratorOutOfBoundsException(std::string && message)
    {
        std::swap(this->message, message);
    }

    IteratorOutOfBoundsException() : message("Iterator out of bounds exception") {}

    std::string& what() {
        return message;
    }
};

class IteratorMismatchException final : public IteratorOutOfBoundsException
{
public:
    explicit IteratorMismatchException(std::string & message) : IteratorOutOfBoundsException(message) {}

    explicit IteratorMismatchException(std::string && message) : IteratorOutOfBoundsException(std::move(message)) {}

    IteratorMismatchException() : IteratorOutOfBoundsException("Iterator mismatch exception"){}
};

#endif //ITERATOROUTOFBOUNDSEXCEPTION_H
