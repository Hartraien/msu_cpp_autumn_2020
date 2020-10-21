#ifndef __CUSTOMPARSER_HPP__
#define __CUSTOMPARSER_HPP__
#include <string>
#include <functional>

// TODO
//Remake callback_func_pointer to actual function pointer
// probably  to std::
using callback_func_pointer = std::function<void (const std::string&)>;

class TokenParser
{
public:
    // default constructor, sets default callback functions
    // see defaultNumberTokenParser and defaultStringTokenParser
    TokenParser();

    // Constructor that sets numberTokenCallback and stringTokenCallback
    // Pass nullptr to use default parser instead
    TokenParser(callback_func_pointer, callback_func_pointer);

    // Sets numberTokenCallback to passed function
    // Pass nullptr to reset numberTokenCallback to defaultNumberTokenParser
    void setNumberTokenCallback(callback_func_pointer);

    // Sets stringTokenCallback to passed function
    // Pass nullptr to reset stringTokenCallback to defaultStringTokenParser
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
    // default parser for number tokens
    // TODO
    // right now does nothing
    void defaultNumberTokenParser(const std::string&);
    
    // default parser for string tokens
    // TODO
    // right now does nothing
    void defaultStringTokenParser(const std::string&);

    // checks whether the token is number or not
    // returns True if number and False otherwise
    bool getTokenType(const std::string&);

    // return pointer for string token callback
    // mostly for testing purposes
    callback_func_pointer getStringTokenCallback();

    // return pointer for number token callback
    // mostly for testing purposes
    callback_func_pointer getNumberTokenCallback();

    // return pointer for start callback
    // mostly for testing purposes
    callback_func_pointer getStartCallback();

    // return pointer for final callback
    // mostly for testing purposes
    callback_func_pointer getFinalCallback();

    void TokenParser::reset();
private:
    // Pointer to callbackfunction that works on numbers
    callback_func_pointer numberTokenCallback;

    // Pointer to callbackfunction that works on strings
    callback_func_pointer stringTokenCallback;

    // Pointer to callbackfunction that works on strings
    callback_func_pointer startCallback;

    // Pointer to callbackfunction that works on strings
    callback_func_pointer finalCallback;

    //
    std::string getNextToken(const std::string&, size_t);
};

#endif //__CUSTOMPARSER_HPP__