#include "TokenParser.hpp"

void TokenParser::parse(const std::string &text)
{
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
