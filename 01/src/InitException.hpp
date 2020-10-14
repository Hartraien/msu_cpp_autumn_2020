#ifndef __INITEXCEPTION_HPP__
#define __INITEXCEPTION_HPP__
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

class InitException : public std::exception
{
public:
    InitException(const std::string &message);
    const char *what() const noexcept override;

private:
    std::string message_;
};

#endif
