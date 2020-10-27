#ifndef __MATRIXTESTER_HPP__
#define __MATRIXTESTER_HPP__

#include "../src/Matrix.hpp"

class MatrixTester
{
public:
    bool test_Constructors();
    bool test_value_operations();
    bool test_printer();

protected:
    bool test_Getter_and_Setters();
    bool test_Summation();
    bool test_Multiplication();
    bool test_Comparison();
    bool test_Constructor_value();
    bool test_Constructor_pointer();
    bool test_Constructor_copy();

private:
    bool check_all_elements_equal_value(const Matrix &, int);
    bool checkSize(const Matrix &, size_t, size_t);
};

#endif // __MATRIXTESTER_HPP__