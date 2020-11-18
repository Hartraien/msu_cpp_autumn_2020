#ifndef __WRONGTEMPLATESTRING_HPP__
#define __WRONGTEMPLATESTRING_HPP__
#include "BaseInclude.hpp"

class WrongTemplateStringException : public std::exception
{
    std::string _msg;

public:
    WrongTemplateStringException(const std::string &msg) : _msg(msg) {}

    virtual const char *what() const noexcept override
    {
        return _msg.c_str();
    }
};

class RightBeforeLeftException : public WrongTemplateStringException
{
public:
    RightBeforeLeftException(const std::string &symbol_left, const std::string &symbol_right, size_t pos_left)
        : WrongTemplateStringException(std::string(symbol_right + " appears before " + symbol_left + " at index " + std::to_string(pos_left))) {}
};

class NoMatchingRightException : public WrongTemplateStringException
{
public:
    NoMatchingRightException(const std::string &symbol_left, const std::string &symbol_right, size_t pos_left) : WrongTemplateStringException(std::string("No matching " + symbol_right + " for " + symbol_left + " at index " + std::to_string(pos_left))) {}
};

#endif // __WRONGTEMPLATESTRING_HPP__