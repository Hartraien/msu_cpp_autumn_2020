#ifndef __NOTANUMBER_HPP__
#define __NOTANUMBER_HPP__
#include "BaseInclude.hpp"

class NotaNumberException : public std::exception
{
    std::string _msg;

public:
    NotaNumberException(const std::string &str, size_t pos) {
        this->_msg = str + " at index " + std::to_string(pos) + " is not a number";
    }

    virtual const char *what() const noexcept override
    {
        return _msg.c_str();
    }
};

#endif // __NOTANUMBER_HPP__