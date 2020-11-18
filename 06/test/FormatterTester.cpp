#include "FormatterTester.hpp"
void FormatterTester::test()
{
    this->test_valid();
    this->test_exception_no_pair();
    this->test_exception_wrong_order();
    this->test_exception_not_a_number();
    this->test_exception_too_large_argument();
}

void FormatterTester::test_valid()
{
    this->test_valid_no_braces();
    this->test_valid_simple();
    this->test_valid_negative();
    this->test_valid_reverse_argument();
    this->test_valid_excess_zeros();
    this->test_valid_excess_arg();
    this->test_valid_custom_class();
    this->test_valid_insert_braces();
}

void FormatterTester::test_exception_no_pair()
{
    this->test_exception_no_pair_instant();
    this->test_exception_no_pair_not_instant();
}

void FormatterTester::test_exception_wrong_order()
{
    this->test_exception_wrong_order_instant();
    this->test_exception_wrong_order_not_instant();
}

void FormatterTester::test_exception_not_a_number()
{
    this->test_exception_not_a_number_no_digits();
    this->test_exception_not_a_number_with_digits();
}

void FormatterTester::test_exception_too_large_argument()
{
    this->test_exception_too_large_argument_pos();
    this->test_exception_too_large_argument_neg();
}

void FormatterTester::test_valid_simple()
{
    std::cout << "Testing simple valid case" << std::endl
              << "\"format(\"{0}+{0} = {1}\", \"one\", 2)\"" << std::endl;

    auto text = format("{0}+{0} = {1}", "one", 2);
    assert(text == "one+one = 2");

    std::cout << "Successfully tested for simple case" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_negative()
{
    std::cout << "Testing valid case with negative argument" << std::endl
              << "\"format(\"{0}+{0} = {-1}\", \"one\", 2)\"" << std::endl;

    auto text = format("{0}+{0} = {-1}", "one", 2);
    assert(text == "one+one = 2");

    std::cout << "Successfully tested for valid case with negative argument" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_no_braces()
{
    std::cout << "Testing valid case without braces and arguments" << std::endl
              << "\"format(\"1+1 = 2\")\"" << std::endl;

    auto text = format("1+1 = 2");
    assert(text == "1+1 = 2");

    std::cout << "Successfully tested for case without braces and arguments" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_reverse_argument()
{
    std::cout << "Testing valid case with format numbers not in order" << std::endl
              << "\"format(\"{1}+{1} = {0}\", 2, \"one\")\"" << std::endl;

    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");

    std::cout << "Successfully tested for case with format numbers not in order" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_excess_zeros()
{
    std::cout << "Testing valid case with excess zeros in format numbers" << std::endl
              << "\"format(\"{001}+{00001} = {00000}\", 2, \"one\")\"" << std::endl;

    auto text = format("{001}+{00001} = {00000}", 2, "one");
    assert(text == "one+one = 2");

    std::cout << "Successfully tested for case with excess zeros in format numbers" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_excess_arg()
{
    std::cout << "Testing valid case with excess arguments" << std::endl
              << "\"format(\"{1}+{1} = {0}\", 2, \"one\", 3, 1)\"" << std::endl;

    auto text = format("{1}+{1} = {0}", 2, "one", 3, 1);
    assert(text == "one+one = 2");

    std::cout << "Successfully tested for case with excess arguments" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_custom_class()
{
    std::cout << "Testing valid case with custom class that implements operator<<()" << std::endl
              << "\"format(\"Custom class print = \\\"{0}\\\"\", custom_class_instance)\"" << std::endl;

    FormatterTester::custom c;
    auto text = format("Custom class print = \"{0}\"", c);
    std::string expected = "Custom class print = \"This is custom class output\"";
    assert(text == expected);

    std::cout << "Successfully tested for case with custom class" << std::endl
              << std::endl;
}

void FormatterTester::test_valid_insert_braces()
{
    std::cout << "Testing valid case with inserting braces and pseudo format numbers" << std::endl
              << "\"format(\"{0}{0} {0}\", \"{1}\", 2)\"" << std::endl;

    auto text = format("{0}{0} {0}", "{1}", 2);
    assert(text == "{1}{1} {1}");

    std::cout << "Successfully tested for case with inserting braces and pseudo numbers" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_no_pair_instant()
{
    std::cout << "Testing exception throwing for case without closing } for the first {" << std::endl
              << "\"format(\"Printing one {0 or not\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "No matching } for { at index 13";
    try
    {
        auto text = format("Printing one {0 or not", 1);
    }
    catch (const NoMatchingRightException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case without closing } for the first {" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_no_pair_not_instant()
{
    std::cout << "Testing exception throwing for case without closing } for not the first {" << std::endl
              << "\"format(\"Printing one {0} and again {0 or not\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "No matching } for { at index 27";
    try
    {
        auto text = format("Printing one {0} and again {0 or not", 1);
    }
    catch (const NoMatchingRightException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case without closing } for not the first {" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_wrong_order_instant()
{
    std::cout << "Testing exception throwing for case where } appears before { and it is the first brace found" << std::endl
              << "\"format(\"Printing one }0{\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "} appears before { at index 13";
    try
    {
        auto text = format("Printing one }0{", 1);
    }
    catch (const RightBeforeLeftException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case where } appears before { and it is the first brace found" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_wrong_order_not_instant()
{
    std::cout << "Testing exception throwing for case where } appears before { and it is not first brace found" << std::endl
              << "\"format(\"Printing one {0} and again }0{ or not\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "} appears before { at index 27";
    try
    {
        auto text = format("Printing one {0} and again }0{ or not", 1);
    }
    catch (const RightBeforeLeftException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case where } appears before { and it is not the first brace found" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_not_a_number_no_digits()
{
    std::cout << "Testing exception throwing for case with not a number in braces" << std::endl
              << "\"format(\"Printing one {a}\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "a at index 14 is not a number";
    try
    {
        auto text = format("Printing one {a}", 1);
    }
    catch (const NotaNumberException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case with not a number in braces" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_not_a_number_with_digits()
{
    std::cout << "Testing exception throwing for case with not a number in braces" << std::endl
              << "\"format(\"Printing one {123a}\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "123a at index 14 is not a number";
    try
    {
        auto text = format("Printing one {123a}", 1);
    }
    catch (const NotaNumberException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case with not a number in braces" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_too_large_argument_pos()
{
    std::cout << "Testing exception throwing for case with too large format number (positive)" << std::endl
              << "\"format(\"Printing {0} {1} {2}\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "Format value (2) at position 14 is larger or equal to number of arguments (2)";
    try
    {
        auto text = format("Printing {0} {1} {2}", 1, 2);
    }
    catch (const TooLargeArgumentException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case with too large format number (positive)" << std::endl
              << std::endl;
}

void FormatterTester::test_exception_too_large_argument_neg()
{
    std::cout << "Testing exception throwing for case with too large format number (negative)" << std::endl
              << "\"format(\"Printing {0} {1} {-3}\", 1)\"" << std::endl;
    std::string res;
    std::string expected = "Format value (3) at position 14 is larger or equal to number of arguments (2)";
    try
    {
        auto text = format("Printing {0} {1} {-3}", 1, 2);
    }
    catch (const TooLargeArgumentException &e)
    {
        res = e.what();
    }
    assert(res == expected);
    std::cout << "Successfully tested exception throwing for case with too large format number (negative)" << std::endl
              << std::endl;
}

std::ostream &operator<<(std::ostream &stream, const FormatterTester::custom &inst)
{
    stream << "This is custom class output";
    return stream;
}
