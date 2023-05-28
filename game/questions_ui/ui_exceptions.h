#ifndef UI_EXCEPTIONS_H
#define UI_EXCEPTIONS_H

#include <stdexcept>

class LoadError : public std::invalid_argument
{
    public:
        LoadError();
};

class WrongIndex : public std::invalid_argument
{
    public:
        WrongIndex(int index);
};

#endif