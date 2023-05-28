#ifndef CLASS_EXCEPTIONS_H
#define CLASS_EXCEPTIONS_H

#include <stdexcept>


class NegativeArgument : public std::invalid_argument
{
    public:
        NegativeArgument(int value);
};

class WrongPath : public std::invalid_argument
{
    public:
        WrongPath(std::string path);
};

class AlreadyDead : public std::invalid_argument
{
    public:
        AlreadyDead(int health);
};

class WrongId : public std::invalid_argument
{
    public:
        WrongId(int id);
};

class OutOfRange : public std::invalid_argument
{
    public:
        OutOfRange(int index);
};

class AlreadyExists : public std::invalid_argument
{
    public:
        AlreadyExists(int id);
};

class DoNotExist : public std::invalid_argument
{
    public:
        DoNotExist(int id);
};

#endif