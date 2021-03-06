#ifndef __BIGINTEGERTESTER_HPP__
#define __BIGINTEGERTESTER_HPP__

#include <iostream>
#include "../src/BigInteger.hpp"

class BigIntegerTester
{
public:
    void test_constructors();
    void test_comparators();
    void test_arithmetic();

    void test_comparison_BI_BI();
    void test_comparison_BI_I();
    void test_comparison_I_BI();

    void test_unary_minus();
    void test_addition();
    void test_subtraction();
    void test_multiplication();
    void test_complex_operations();
};

#endif // __BIGINTEGERTESTER_HPP__