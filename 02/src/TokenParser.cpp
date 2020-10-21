#include "TokenParser.hpp"
#include <iostream>

void TokenParser::parse(const std::string &text)
{
    size_t pos = 0;
    this->startCallback(text);
    while (pos < text.length())
    {
        std::string token = this->getNextToken(text, pos);
        if (token.length() != 0)
        {
            if (getTokenType(token))
            {
                this->numberTokenCallback(token);
            }
            else
            {
                this->stringTokenCallback(token);
            }
        }
        pos = pos + token.length() + 1;
    }
    this->finalCallback(text);
    return;
}

void TokenParser::defaultNumberTokenParser(const std::string &)
{
    return;
}

void TokenParser::defaultStringTokenParser(const std::string &)
{
    return;
}

void TokenParser::defaultStartParser(const std::string &) 
{
    return;
}

void TokenParser::defaultFinalParser(const std::string &) 
{
    return;
}

bool TokenParser::getTokenType(const std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

callback_func_pointer TokenParser::getStringTokenCallback()
{
    return this->stringTokenCallback;
}

callback_func_pointer TokenParser::getNumberTokenCallback()
{
    return this->numberTokenCallback;
}

callback_func_pointer TokenParser::getStartCallback()
{
    return this->startCallback;
}

callback_func_pointer TokenParser::getFinalCallback()
{
    return this->finalCallback;
}

std::string TokenParser::getNextToken(const std::string &text, size_t pos)
{
    std::string delimeters = " \t\n";
    size_t new_pos = text.find_first_of(delimeters, pos);
    if (new_pos == std::string::npos)
    {
        new_pos = text.length();
    }
    return text.substr(pos, new_pos - pos);
}
TokenParser::TokenParser()
{
    this->numberTokenCallback = [this](const std::string &token) { this->defaultNumberTokenParser(token); };
    this->stringTokenCallback = [this](const std::string &token) { this->defaultStringTokenParser(token); };
    this->startCallback = [this](const std::string &token) { this->defaultStartParser(token); };
    this->finalCallback = [this](const std::string &token) { this->defaultFinalParser(token); };
}

TokenParser::TokenParser(callback_func_pointer numberTokenCallback, callback_func_pointer stringTokenCallback) : TokenParser()
{
    this->setNumberTokenCallback(numberTokenCallback);
    this->setStringTokenCallback(stringTokenCallback);
}

void TokenParser::setNumberTokenCallback(callback_func_pointer numberTokenCallback)
{
    if (numberTokenCallback != nullptr)
    {
        this->numberTokenCallback = numberTokenCallback;
    }
    else
    {
        this->numberTokenCallback = [this](const std::string &token) { this->defaultNumberTokenParser(token); };
    }
}

void TokenParser::setStringTokenCallback(callback_func_pointer stringTokenCallback)
{
    if (stringTokenCallback != nullptr)
    {
        this->stringTokenCallback = stringTokenCallback;
    }
    else
    {
        this->stringTokenCallback = [this](const std::string &token) { this->defaultStringTokenParser(token); };
    }
}

void TokenParser::setStartCallback(callback_func_pointer startCallback)
{
    if (startCallback != nullptr)
    {
        this->startCallback = startCallback;
    }
    else
    {
        this->startCallback = [this](const std::string &token) { this->defaultStartParser(token); };
    }
}

void TokenParser::setFinalCallback(callback_func_pointer finalCallback)
{
    if (finalCallback != nullptr)
    {
        this->finalCallback = finalCallback;
    }
    else
    {
        this->finalCallback = [this](const std::string &token) { this->defaultFinalParser(token); };
    }
    
}

void TokenParser::reset()
{
    this->setNumberTokenCallback(nullptr);
    this->setStringTokenCallback(nullptr);
    this->setStartCallback(nullptr);
    this->setFinalCallback(nullptr);
}
