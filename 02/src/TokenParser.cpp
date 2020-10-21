#include "TokenParser.hpp"

void TokenParser::parse(const std::string &text)
{
    size_t pos = 0;
    if (this->startCallback)
    {
        this->startCallback(text);
    }

    while (pos != text.length())
    {
        std::string token = this->getNextToken(text, pos);
        if (getTokenType(token))
        {
            this->numberTokenCallback(token);
        }
        else
        {
            this->stringTokenCallback(token);
        }
        pos = pos + token.length();
        
    }

    if (this->finalCallback)
    {
        this->finalCallback(text);
    }
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

bool TokenParser::getTokenType(const std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
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
    this->startCallback = nullptr;
    this->finalCallback = nullptr;
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
    this->startCallback = startCallback;
}

void TokenParser::setFinalCallback(callback_func_pointer finalCallback)
{
    this->finalCallback = finalCallback;
}
