#ifndef __CUSTOMPARSER_HPP__
#define __CUSTOMPARSER_HPP__
#include <string>
#include <functional>

//TODO
//Remake callback_func_pointer to actual function pointer
// probably  to std::
using callback_func_pointer = void *;

class TokenParser
{
public:
    // default constructor, sets default callback functions
    // see defaultNumberParser and defaultStringParser
    TokenParser();

    // Constructor that sets numberTokenCallback and stringTokenCallback
    // Pass nullptr to use default parser instead
    TokenParser(callback_func_pointer, callback_func_pointer);

    // Sets numberTokenCallback to passed function
    // Pass nullptr to reset numberTokenCallback to defaultNumberPArser
    void setNumberTokenCallback(callback_func_pointer);

    // Sets stringTokenCallback to passed function
    // Pass nullptr to reset stringTokenCallback to defaultNumberParser
    void setStringTokenCallback(callback_func_pointer);

    // Sets callback function that is called before parsing
    // Pass nullptr to reset to default
    void setStartCallback(callback_func_pointer);

    // Sets callback function that is called after parsing
    // Pass nullptr to reset to default
    void setFinalCallback(callback_func_pointer);

    // Parses input text using
    void parse(const std::string &);

protected:
private:
    // Pointer to callbackfunctionm that works on numbers
    callback_func_pointer numberTokenCallback;

    // Pointer to callbackfunctionm that works on strings
    callback_func_pointer stringTokenCallback;

    // Pointer to callbackfunctionm that works on strings
    callback_func_pointer startCallbackFunc;

    // Pointer to callbackfunctionm that works on strings
    callback_func_pointer finalCallbackFunc;
};

#endif