#ifndef __FORMATTERTESTER_HPP__
#define __FORMATTERTESTER_HPP__
#include <iostream>
#include <cassert>
#include "../src/Formatter.hpp"

class FormatterTester
{
public:
    void test();

    void test_valid();
    void test_exception_no_pair();
    void test_exception_wrong_order();
    void test_exception_not_a_number();
    void test_too_large_number();
    void test_exception_too_large_argument();

    void test_valid_simple();
    void test_valid_negative();
    void test_valid_no_braces();
    void test_valid_reverse_argument();
    void test_valid_excess_zeros();
    void test_valid_excess_arg();
    void test_valid_custom_class();
    void test_valid_insert_braces();

    void test_exception_no_pair_instant();
    void test_exception_no_pair_not_instant();

    void test_exception_wrong_order_instant();
    void test_exception_wrong_order_not_instant();

    void test_exception_not_a_number_no_digits();
    void test_exception_not_a_number_with_digits();

    void test_too_large_number_impl();

    void test_exception_too_large_argument_pos();
    void test_exception_too_large_argument_neg();

public:
    class custom
    {
    public:
        friend std::ostream &operator<<(std::ostream &stream, const custom &inst);
    };
};

#endif // __FORMATTERTESTER_HPP__