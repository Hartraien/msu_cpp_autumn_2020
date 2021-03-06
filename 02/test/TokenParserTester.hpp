#ifndef __TOKENPARSERTESTER_HPP__
#define __TOKENPARSERTESTER_HPP__

#include "../src/TokenParser.hpp"

class TokenParserTester : protected TokenParser
{
public:
    TokenParserTester();
    void test_setNumberTokenCallback();
    void test_setStringTokenCallback();
    void test_setStartCallback();
    void test_setFinalCallback();
    void test_parse();
    void test_parse_default();
    void test_parse_customTokenCallback();
    void test_parse_customStartFinalCallback();
    void test_parse_allCustom();

private:
    std::string test_text;
    std::string test_empty_text;
    std::string test_delim_only_text;
};

#endif // __TOKENPARSERTESTER_HPP__