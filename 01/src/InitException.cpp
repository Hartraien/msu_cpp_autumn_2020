#include <exception>
#include <string>

#include "InitException.hpp"
InitException::InitException(const std::string &message) : message_(message)
{
}

const char *InitException::what() const noexcept
{
    return this->message_.c_str();
}