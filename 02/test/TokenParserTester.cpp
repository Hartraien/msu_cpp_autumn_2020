#include "TokenParserTester.hpp"
#include <iostream>
#include <cassert>
#include <sstream>

void testStringtokenCallback(const std::string &s);
void testNumbertokenCallback(const std::string &s);
void testStartCallback(const std::string &s);
void testFinalCallback(const std::string &s);

using pointer_to_func = void (*)(const std::string &);

void TokenParserTester::test_setNumberTokenCallback()
{
    std::string res1, res2;
    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;

    // testing pointers

    std::cout << "Testing for passing pointer to numberTokenCallback" << std::endl;
    pointer_to_func p = testNumbertokenCallback;
    this->setNumberTokenCallback(p);
    callback_func_pointer inner_p = this->getNumberTokenCallback();

    try
    {
        std::cout.rdbuf(tempCout.rdbuf());
        p("test");
        inner_p("test");
        std::getline(tempCout, res1);
        std::getline(tempCout, res2);
        std::cout.rdbuf(oldStdoutBuf);
        tempCout.clear();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout.rdbuf(oldStdoutBuf);
    assert(res1 == res2);
    res1.clear();
    res2.clear();
    std::cout << "Successfully passed pointer to numberTokenCallback" << std::endl;
    this->reset();

    // testing lambdas

    std::cout << "Testing for passing lambda to numberTokenCallback" << std::endl;
    auto l = [](const std::string &a) { std::cout << "lambda function named 'l' text equals " << a << std::endl; };
    this->setNumberTokenCallback(l);
    callback_func_pointer inner_l = this->getNumberTokenCallback();

    try
    {
        std::cout.rdbuf(tempCout.rdbuf());
        l("test");
        inner_l("test");
        std::getline(tempCout, res1);
        std::getline(tempCout, res2);
        std::cout.rdbuf(oldStdoutBuf);
        tempCout.clear();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout.rdbuf(oldStdoutBuf);
    assert(res1 == res2);
    res1.clear();
    res2.clear();
    std::cout << "Successfully passed lambda to numberTokenCallback" << std::endl;
    this->reset();

    // testing std::function

    std::cout << "Testing for passing std::function to numberTokenCallback" << std::endl;
    auto f = std::function<void(const std::string &a)>(testNumbertokenCallback);
    this->setNumberTokenCallback(f);
    callback_func_pointer inner_f = this->getNumberTokenCallback();

    try
    {
        std::cout.rdbuf(tempCout.rdbuf());
        f("test");
        inner_f("test");
        std::getline(tempCout, res1);
        std::getline(tempCout, res2);
        std::cout.rdbuf(oldStdoutBuf);
        tempCout.clear();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout.rdbuf(oldStdoutBuf);
    assert(res1 == res2);
    res1.clear();
    res2.clear();
    std::cout << "Successfully passed std::function to numberTokenCallback" << std::endl;
    this->reset();
}

void TokenParserTester::test_setStringTokenCallback()
{
}

void TokenParserTester::test_setStartCallback()
{
}

void TokenParserTester::test_setFinalCallback()
{
}

void TokenParserTester::test_parse()
{
}

void TokenParserTester::test_parse_default()
{
}

void TokenParserTester::test_parse_customTokenCallback()
{
}

void TokenParserTester::test_parse_customStartFinalCallback()
{
}

void TokenParserTester::test_parse_allCustom()
{
}

TokenParserTester::TokenParserTester() : TokenParser()
{
}

void testStringtokenCallback(const std::string &s)
{
}

void testNumbertokenCallback(const std::string &s)
{
    std::cout << "pointer function named 'p' text equals " << s << std::endl;
}