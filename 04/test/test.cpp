#include "BigIntegerTester.hpp"

int main()
{
    BigIntegerTester bigIntegerTester;
    bigIntegerTester.test_constructors();
    bigIntegerTester.test_comparators();
    bigIntegerTester.test_arithmetic();
    return 0;
}