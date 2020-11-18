#ifndef __NOTANUMBER_HPP__
#define __NOTANUMBER_HPP__
#include "BaseInclude.hpp"

class NotaNumberException : public std::exception
{
    std::string msg_;

public:
    NotaNumberException(const std::string &str, size_t pos)
    {
        this->msg_ = str + " at index " + std::to_string(pos) + " is not a number";
    }

    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }
};

#endif // __NOTANUMBER_HPP__