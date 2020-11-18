#ifndef __TOOLARGENUMBER_HPP__
#define __TOOLARGENUMBER_HPP__
#include "BaseInclude.hpp"

class TooLargeNumberException : public std::exception
{
    std::string msg_;

public:
    TooLargeNumberException(const std::string &str, size_t pos)
    {
        this->msg_ = "Number " + str + " at index " + std::to_string(pos) + " is too large";
    }

    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }
};

#endif // __TOOLARGENUMBER_HPP__