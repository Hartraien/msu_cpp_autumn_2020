#include "TokenParserTester.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

void testStringTokenCallback(const std::string &s);
void testNumberTokenCallback(const std::string &s);
void testStartCallback(const std::string &s);
void testFinalCallback(const std::string &s);

using pointer_to_func = void (*)(const std::string &);

void TokenParserTester::test_setNumberTokenCallback()
{
    std::cout << "!! Testing TokenParser::setNumberTokenCallback method !!" << std::endl;
    std::cout << "This test will sequentially pass pointer, lambda function and std::function object to numberTokenCallback of TokenParser Instance" << std::endl;
    std::cout << "Then get numberTokenCallback from TokenParser Instance" << std::endl;
    std::cout << "Call both of them" << std::endl;
    std::cout << "And compare their output - it is expected to be equal" << std::endl;

    std::string res1, res2;
    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;

    // testing pointers

    std::cout << "Testing for passing pointer to numberTokenCallback" << std::endl;
    pointer_to_func p = testNumberTokenCallback;
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
    auto l = [](const std::string &a) { std::cout << "lambda function named 'l' in number token callback testing text equals " << a << std::endl; };
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
    auto f = std::function<void(const std::string &a)>(testNumberTokenCallback);
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

    std::cout << "!! Successfully tested setNumberTokenCallback Method !!" << std::endl;
}

void TokenParserTester::test_setStringTokenCallback()
{
    std::cout << "!! Testing TokenParser::setStringTokenCallback method !!" << std::endl;
    std::cout << "This test will sequentially pass pointer, lambda function and std::function object to stringTokenCallback of TokenParser Instance" << std::endl;
    std::cout << "Then get stringTokenCallback from TokenParser Instance" << std::endl;
    std::cout << "Call both of them" << std::endl;
    std::cout << "And compare their output - it is expected to be equal" << std::endl;

    std::string res1, res2;
    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;

    // testing pointers

    std::cout << "Testing for passing pointer to stringTokenCallback" << std::endl;
    pointer_to_func p = testStringTokenCallback;
    this->setStringTokenCallback(p);
    callback_func_pointer inner_p = this->getStringTokenCallback();

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
    std::cout << "Successfully passed pointer to stringTokenCallback" << std::endl;
    this->reset();

    // testing lambdas

    std::cout << "Testing for passing lambda to stringTokenCallback" << std::endl;
    auto l = [](const std::string &a) { std::cout << "lambda function named 'l' in string token callback testing text equals " << a << std::endl; };
    this->setStringTokenCallback(l);
    callback_func_pointer inner_l = this->getStringTokenCallback();

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
    std::cout << "Successfully passed lambda to stringTokenCallback" << std::endl;
    this->reset();

    // testing std::function

    std::cout << "Testing for passing std::function to stringTokenCallback" << std::endl;
    auto f = std::function<void(const std::string &a)>(testStringTokenCallback);
    this->setStringTokenCallback(f);
    callback_func_pointer inner_f = this->getStringTokenCallback();

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
    std::cout << "Successfully passed std::function to stringTokenCallback" << std::endl;
    this->reset();

    std::cout << "!! Successfully tested setStringTokenCallback Method !!" << std::endl;
}

void TokenParserTester::test_setStartCallback()
{
    std::cout << "!! Testing TokenParser::setStartCallback method !!" << std::endl;
    std::cout << "This test will sequentially pass pointer, lambda function and std::function object to startCallback of TokenParser Instance" << std::endl;
    std::cout << "Then get startCallback from TokenParser Instance" << std::endl;
    std::cout << "Call both of them" << std::endl;
    std::cout << "And compare their output - it is expected to be equal" << std::endl;

    std::string res1, res2;
    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;

    // testing pointers

    std::cout << "Testing for passing pointer to startCallback" << std::endl;
    pointer_to_func p = testStartCallback;
    this->setStartCallback(p);
    callback_func_pointer inner_p = this->getStartCallback();

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
    std::cout << "Successfully passed pointer to startCallback" << std::endl;
    this->reset();

    // testing lambdas

    std::cout << "Testing for passing lambda to startCallback" << std::endl;
    auto l = [](const std::string &a) { std::cout << "lambda function named 'l' in start callback testing text equals " << a << std::endl; };
    this->setStartCallback(l);
    callback_func_pointer inner_l = this->getStartCallback();

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
    std::cout << "Successfully passed lambda to startCallback" << std::endl;
    this->reset();

    // testing std::function

    std::cout << "Testing for passing std::function to startCallback" << std::endl;
    auto f = std::function<void(const std::string &a)>(testStartCallback);
    this->setStartCallback(f);
    callback_func_pointer inner_f = this->getStartCallback();

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
    std::cout << "Successfully passed std::function to startCallback" << std::endl;
    this->reset();

    std::cout << "!! Successfully tested setStartCallback Method !!" << std::endl;
}

void TokenParserTester::test_setFinalCallback()
{
    std::cout << "!! Testing TokenParser::setFinalCallback method !!" << std::endl;
    std::cout << "This test will sequentially pass pointer, lambda function and std::function object to finalCallback of TokenParser Instance" << std::endl;
    std::cout << "Then get finalCallback from TokenParser Instance" << std::endl;
    std::cout << "Call both of them" << std::endl;
    std::cout << "And compare their output - it is expected to be equal" << std::endl;

    std::string function_output, passed_function_output;
    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;

    // testing pointers

    std::cout << "Testing for passing pointer to finalCallback" << std::endl;
    pointer_to_func p = testFinalCallback;
    this->setFinalCallback(p);
    callback_func_pointer inner_p = this->getFinalCallback();

    try
    {
        std::cout.rdbuf(tempCout.rdbuf());
        p("test");
        inner_p("test");
        std::getline(tempCout, function_output);
        std::getline(tempCout, passed_function_output);
        std::cout.rdbuf(oldStdoutBuf);
        tempCout.clear();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout.rdbuf(oldStdoutBuf);
    assert(function_output == passed_function_output);
    function_output.clear();
    passed_function_output.clear();
    std::cout << "Successfully passed pointer to finalCallback" << std::endl;
    this->reset();

    // testing lambdas

    std::cout << "Testing for passing lambda to finalCallback" << std::endl;
    auto l = [](const std::string &a) { std::cout << "lambda function named 'l' in final callback testing text equals " << a << std::endl; };
    this->setFinalCallback(l);
    callback_func_pointer inner_l = this->getFinalCallback();

    try
    {
        std::cout.rdbuf(tempCout.rdbuf());
        l("test");
        inner_l("test");
        std::getline(tempCout, function_output);
        std::getline(tempCout, passed_function_output);
        std::cout.rdbuf(oldStdoutBuf);
        tempCout.clear();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout.rdbuf(oldStdoutBuf);
    assert(function_output == passed_function_output);
    function_output.clear();
    passed_function_output.clear();
    std::cout << "Successfully passed lambda to finalCallback" << std::endl;
    this->reset();

    // testing std::function

    std::cout << "Testing for passing std::function to finalCallback" << std::endl;
    auto f = std::function<void(const std::string &a)>(testFinalCallback);
    this->setFinalCallback(f);
    callback_func_pointer inner_f = this->getFinalCallback();

    try
    {
        std::cout.rdbuf(tempCout.rdbuf());
        f("test");
        inner_f("test");
        std::getline(tempCout, function_output);
        std::getline(tempCout, passed_function_output);
        std::cout.rdbuf(oldStdoutBuf);
        tempCout.clear();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout.rdbuf(oldStdoutBuf);
    assert(function_output == passed_function_output);
    function_output.clear();
    passed_function_output.clear();
    std::cout << "Successfully passed std::function to finalCallback" << std::endl;
    this->reset();

    std::cout << "!! Successfully tested setFinalCallback Method !!" << std::endl;
}

void TokenParserTester::test_parse()
{
    std::cout << std::endl
              << std::endl;
    std::cout << "!! Testing TokenParser::parse() method !!" << std::endl;
    std::cout << std::endl
              << std::endl;
    this->test_parse_default();
    std::cout << std::endl
              << std::endl;
    this->test_parse_customTokenCallback();
    std::cout << std::endl
              << std::endl;
    this->test_parse_customStartFinalCallback();
    std::cout << std::endl
              << std::endl;
    this->test_parse_allCustom();
    std::cout << std::endl
              << std::endl;
    std::cout << "!! Successfully tested TokenParser::parse() method !!" << std::endl;
}

void TokenParserTester::test_parse_default()
{
    std::cout << "Testing default parser (with default callback functions), that does nothing" << std::endl;
    std::cout << "Expected output - empty std::cout" << std::endl;
    std::cout << "This test temporary overrides std::cout to check output" << std::endl;

    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;
    std::cout.rdbuf(tempCout.rdbuf());

    this->parse(this->test_text);

    std::string overriden_cout;
    tempCout >> overriden_cout;

    this->parse(this->test_empty_text);

    tempCout >> overriden_cout;

    assert(overriden_cout.length() == 0);

    tempCout.clear();
    std::cout.rdbuf(oldStdoutBuf);

    std::cout << "Successfully tested default parse" << std::endl;
    this->reset();
}

void TokenParserTester::test_parse_customTokenCallback()
{
    std::cout << "Testing parser (with custom token callback functions)" << std::endl;
    std::cout << "Expected output: empty std::cout and two vectors of tokens" << std::endl;
    std::cout << "This test temporary overrides std::cout to check output" << std::endl;

    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;
    std::cout.rdbuf(tempCout.rdbuf());

    std::vector<std::string> number_parser_output, string_parser_output;
    std::vector<std::string> number_parser_output_expected{"231", "123"};
    std::vector<std::string> string_parser_output_expected{"asdfa", "123asdw", "-21", "asd213", "dadw", "sadwe"};

    auto l1 = [&number_parser_output](const std::string &a) { number_parser_output.push_back(a); };
    auto l2 = [&string_parser_output](const std::string &a) { string_parser_output.push_back(a); };

    this->setNumberTokenCallback(l1);
    this->setStringTokenCallback(l2);

    this->parse(this->test_empty_text);
    assert(number_parser_output.size() == 0);
    assert(string_parser_output.size() == 0);
    this->parse(this->test_text);

    std::string overriden_cout;
    tempCout >> overriden_cout;

    assert(overriden_cout.length() == 0);
    assert(number_parser_output == number_parser_output_expected);
    assert(string_parser_output == string_parser_output_expected);

    tempCout.clear();
    std::cout.rdbuf(oldStdoutBuf);

    std::cout << "Successfully tested parser with custom token callback functions" << std::endl;
    this->reset();
}

void TokenParserTester::test_parse_customStartFinalCallback()
{
    std::cout << "Testing parser (with custom callback functions)" << std::endl;
    std::cout << "Expected output: 'start Callback' and 'final Callback' to std::cout" << std::endl;
    std::cout << "This test temporary overrides std::cout to check output" << std::endl;

    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;
    std::cout.rdbuf(tempCout.rdbuf());

    auto l1 = [](const std::string &a) { std::cout << "start Callback" << std::endl; };
    auto l2 = [](const std::string &a) { std::cout << "final Callback" << std::endl; };

    this->setStartCallback(l1);
    this->setFinalCallback(l2);

    this->parse(this->test_text);

    std::string start_callback_output, final_callback_output;
    std::getline(tempCout, start_callback_output);
    std::getline(tempCout, final_callback_output);
    assert(start_callback_output == "start Callback");
    assert(final_callback_output == "final Callback");
    tempCout.clear();
    start_callback_output.clear();
    final_callback_output.clear();

    this->parse(this->test_empty_text);

    std::getline(tempCout, start_callback_output);
    std::getline(tempCout, final_callback_output);
    assert(start_callback_output == "start Callback");
    assert(final_callback_output == "final Callback");
    tempCout.clear();
    start_callback_output.clear();
    final_callback_output.clear();

    tempCout.clear();
    std::cout.rdbuf(oldStdoutBuf);

    std::cout << "Successfully tested parser with custom start and final callbacks" << std::endl;
    this->reset();
}

void TokenParserTester::test_parse_allCustom()
{
    std::cout << "Testing parser (with custom token callback functions)" << std::endl;
    std::cout << "Expected output: 'start Callback' and 'final Callback' to std::cout and two vectors of tokens" << std::endl;
    std::cout << "This test temporary overrides std::cout to check output" << std::endl;

    auto oldStdoutBuf = std::cout.rdbuf();
    std::stringstream tempCout;
    std::cout.rdbuf(tempCout.rdbuf());

    std::vector<std::string> number_parser_output, string_parser_output;
    std::vector<std::string> number_parser_output_expected{"231", "123"};
    std::vector<std::string> string_parser_output_expected{"asdfa", "123asdw", "-21", "asd213", "dadw", "sadwe"};

    auto l1 = [](const std::string &a) { std::cout << "start Callback" << std::endl; };
    auto l2 = [](const std::string &a) { std::cout << "final Callback" << std::endl; };

    auto l3 = [&number_parser_output](const std::string &a) { number_parser_output.push_back(a); };
    auto l4 = [&string_parser_output](const std::string &a) { string_parser_output.push_back(a); };

    this->setNumberTokenCallback(l3);
    this->setStringTokenCallback(l4);

    this->setStartCallback(l1);
    this->setFinalCallback(l2);

    this->parse(this->test_empty_text);

    std::string start_callback_output, final_callback_output;
    std::getline(tempCout, start_callback_output);
    std::getline(tempCout, final_callback_output);
    assert(start_callback_output == "start Callback");
    assert(final_callback_output == "final Callback");
    assert(number_parser_output.size() == 0);
    assert(string_parser_output.size() == 0);
    tempCout.clear();
    start_callback_output.clear();
    final_callback_output.clear();

    this->parse(this->test_text);

    std::getline(tempCout, start_callback_output);
    std::getline(tempCout, final_callback_output);
    assert(start_callback_output == "start Callback");
    assert(final_callback_output == "final Callback");
    assert(number_parser_output == number_parser_output_expected);
    assert(string_parser_output == string_parser_output_expected);
    tempCout.clear();
    start_callback_output.clear();
    final_callback_output.clear();

    tempCout.clear();
    std::cout.rdbuf(oldStdoutBuf);

    std::cout << "Successfully tested parser with all custom callbacks" << std::endl;

    this->reset();
}

TokenParserTester::TokenParserTester() : TokenParser()
{
    this->test_text = "asdfa 123asdw 231 -21 asd213     dadw        \n sadwe 123 ";
    this->test_empty_text = "";
    this->test_delim_only_text = "  \n";
}

void testStringTokenCallback(const std::string &s)
{
    std::cout << "This is testStringTokenCallback pointer function named 'p' text equals " << s << std::endl;
}

void testNumberTokenCallback(const std::string &s)
{
    std::cout << "This is testNumberTokenCallback pointer function named 'p' text equals " << s << std::endl;
}

void testStartCallback(const std::string &s)
{
    std::cout << "This is testStartCallback pointer function named 'p' text equals " << s << std::endl;
}

void testFinalCallback(const std::string &s)
{
    std::cout << "This is testFinalCallback pointer function named 'p' text equals " << s << std::endl;
}