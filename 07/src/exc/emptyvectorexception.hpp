#ifndef __EMPTYVECTOREXCEPTION_H__
#define __EMPTYVECTOREXCEPTION_H__
#include "BaseInclude.hpp"

class EmptyVectorException : public std::exception
{
    std::string msg_;

public:
    EmptyVectorException(const std::string &msg)
    {
        this->msg_ = "Vector is empty, it's impossible to call method " + msg;
    }

    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }
};

#endif // __EMPTYVECTOREXCEPTION_H__