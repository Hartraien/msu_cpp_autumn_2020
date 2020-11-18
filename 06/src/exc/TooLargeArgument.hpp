#ifndef __TOOLARGEARGUMENT_HPP__
#define __TOOLARGEARGUMENT_HPP__
#include "BaseInclude.hpp"

class TooLargeArgumentException : public std::exception
{
    std::string _msg;

public:
    TooLargeArgumentException(const size_t &pos, const size_t &val, const size_t &max_val)
    {
        this->_msg = "Format value (" + std::to_string(val) + ") at position " + std::to_string(pos) + " is larger or equal to number of arguments (" + std::to_string(max_val) + ")";
    }

    virtual const char *what() const noexcept override
    {
        return _msg.c_str();
    }
};

#endif // __TOOLARGEARGUMENT_HPP__