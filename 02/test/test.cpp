#include "TokenParserTester.hpp"
#include <memory>
#include <iostream>


int main(int argc, char **argv)
{
    std::unique_ptr<TokenParserTester> tokenParserTester = std::make_unique<TokenParserTester>();
    tokenParserTester->test_setNumberTokenCallback();
    std::cout << std::endl
              << "All tests were passed successfully"
              << std::endl;
}