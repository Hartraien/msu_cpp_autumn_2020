#ifndef __TOKENPARSERTESTER_H__
#define __TOKENPARSERTESTER_H__

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
protected:
    void reset();
};

#endif // __TOKENPARSERTESTER_H__