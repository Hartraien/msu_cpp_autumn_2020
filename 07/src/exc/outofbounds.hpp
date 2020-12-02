#ifndef __OUTOFBOUNDS_H__
#define __OUTOFBOUNDS_H__
#include "BaseInclude.hpp"

class OOBException : public std::exception
{
    std::string msg_;

public:
    OOBException(size_t index, size_t size)
    {
        this->msg_ = "Index " + std::to_string(index) + " is out of bounds for vector of size " + std::to_string(size);
    }

    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }
};
#endif // __OUTOFBOUNDS_H__