#include "TokenParserTester.hpp"
#include <memory>
#include <iostream>

int main(int argc, char **argv)
{
    std::unique_ptr<TokenParserTester> tokenParserTester = std::make_unique<TokenParserTester>();
    std::cout << "This test will test methods of TokenParser in this order:" << std::endl;
    std::cout << "TokenParser::setNumberTokenCallback" << std::endl;
    std::cout << "TokenParser::setStringTokenCallback" << std::endl;
    std::cout << "TokenParser::setStartCallback" << std::endl;
    std::cout << "TokenParser::setFinalCallback" << std::endl;
    std::cout << "TokenParser::parse" << std::endl;
    std::cout << "TokenParser::parse will be tested with both default and custom callback functions (in different combinations)" << std::endl;
    std::cout << std::endl
              << std::endl;
    tokenParserTester->test_setNumberTokenCallback();
    std::cout << std::endl
              << std::endl;
    tokenParserTester->test_setStringTokenCallback();
    std::cout << std::endl
              << std::endl;
    tokenParserTester->test_setStartCallback();
    std::cout << std::endl
              << std::endl;
    tokenParserTester->test_setFinalCallback();
    std::cout << std::endl
              << std::endl;
    tokenParserTester->test_parse();
    std::cout << std::endl
              << "!!!!  All tests were passed successfully  !!!!"
              << std::endl;
}