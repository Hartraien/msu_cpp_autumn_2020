#include <memory>
#include <iostream>
#include <cassert>
#include <sstream>
#include "MatrixTester.hpp"
bool MatrixTester::test_Constructors()
{
    std::cout << "!! Testing different Matrix constructors !!" << std::endl;
    std::cout << "Testing Matrix(row_count, col_count, value) constructor" << std::endl;
    assert(true == this->test_Constructor_value());
    std::cout << "Successfully tested Matrix(row_count, col_count, value) constructor" << std::endl;

    std::cout << "Testing Matrix(row_count, col_count, value) constructor" << std::endl;
    assert(true == this->test_Constructor_pointer());
    std::cout << "Successfully tested Matrix(row_count, col_count, int_pointer) constructor" << std::endl;

    std::cout << "Testing Matrix(const Matrix&) constructor" << std::endl;
    assert(true == this->test_Constructor_copy());
    std::cout << "Successfully tested Matrix(const Matrix&) constructor" << std::endl;
    std::cout << "!! Successfully tested different Matrix constructors !!" << std::endl
              << std::endl;
    return true;
}

bool MatrixTester::test_Getter_and_Setters()
{
    size_t rows = 5;
    size_t cols = 4;
    int value = 2;
    int i1 = 0;
    Matrix m(rows, cols, value);

    std::cout << "Testing Matrix getter within bounds" << std::endl;
    assert(m[1][1] == 2);
    std::cout << "Successfully tested Matrix getter within bounds" << std::endl;

    std::cout << "Testing Matrix setter within bounds" << std::endl;
    m[1][1] = 3;
    assert(m[1][1] == 3);
    assert(m[0][0] == value);
    std::cout << "Successfully tested Matrix setter within bounds" << std::endl;

    bool caught = false;

    std::cout << "Testing Matrix getter out of bounds" << std::endl;
    try
    {
        i1 = 0;
        i1 = m[0][cols + 1];
    }
    catch (const std::out_of_range &e)
    {
        caught = true;
    }
    assert(caught == true);
    assert(i1 == 0);
    caught = false;

    try
    {
        i1 = 0;
        i1 = m[rows + 1][0];
    }
    catch (const std::out_of_range &e)
    {
        caught = true;
    }
    assert(caught == true);
    assert(i1 == 0);
    caught = false;

    try
    {
        i1 = 0;
        i1 = m[rows + 1][cols + 1];
    }
    catch (const std::out_of_range &e)
    {
        caught = true;
    }
    assert(caught == true);
    assert(i1 == 0);
    caught = false;

    std::cout << "Successfully tested Matrix getter within bounds" << std::endl;

    std::cout << "Testing Matrix setter out of bounds" << std::endl;
    try
    {
        m[0][cols + 1] = -1;
    }
    catch (const std::out_of_range &e)
    {
        caught = true;
    }
    assert(caught == true);
    caught = false;

    try
    {
        m[rows + 1][0] = -1;
    }
    catch (const std::out_of_range &e)
    {
        caught = true;
    }
    assert(caught == true);
    caught = false;

    try
    {
        m[rows + 1][cols + 1] = -1;
    }
    catch (const std::out_of_range &e)
    {
        caught = true;
    }
    assert(caught == true);
    caught = false;

    std::cout << "Successfully tested Matrix setter out of bounds" << std::endl;

    return true;
}

bool MatrixTester::test_value_operations()
{
    std::cout << "!! Testing Matrix getter and setter !!" << std::endl;
    assert(true == this->test_Getter_and_Setters());
    std::cout << "!! Successfully tested Matrix getter and setter !!" << std::endl
              << std::endl;

    std::cout << "!! Testing Matrix comparison operator !!" << std::endl;
    assert(true == this->test_Comparison());
    std::cout << "!! Successfully tested Matrix comparison operator !!" << std::endl
              << std::endl;

    std::cout << "!! Testing Matrix + Matrix and Matrix - Matrix operators !!" << std::endl;
    assert(true == this->test_Summation());
    std::cout << "!! Successfully tested Matrix + Matrix and Matrix - Matrix operators !!" << std::endl
              << std::endl;

    std::cout << "!! Testing Matrix * int operator !!" << std::endl;
    assert(true == this->test_Multiplication());
    std::cout << "!! Successfully tested Matrix * int operator !!" << std::endl
              << std::endl;
    return true;
}

bool MatrixTester::test_Summation()
{
    size_t rows = 5;
    size_t cols = 4;
    Matrix m1(rows, cols, 4);
    Matrix m2(rows, cols, 5);
    Matrix m3(rows, cols, 9);
    Matrix m4(m1), m5(m2), m6(m3);
    Matrix m_diff(rows + 1, cols, 20);
    bool caught;

    std::cout << "Testing Matrix += Matrix (same size) operator" << std::endl;
    assert((m4 += m5) == m6);
    std::cout << "Successfully tested Matrix += Matrix (same size) operator" << std::endl;

    std::cout << "Testing Matrix += Matrix (different size) operator" << std::endl;
    caught = false;
    try
    {
        m1 += m_diff;
    }
    catch (const std::exception &e)
    {
        caught = true;
    }
    assert(caught == true);

    std::cout << "Successfully tested Matrix += Matrix (different size) operator" << std::endl;

    std::cout << "Testing Matrix -= Matrix (same size) operator" << std::endl;
    assert((m4 -= m5) == m1);
    std::cout << "Successfully tested Matrix -= Matrix (same size) operator" << std::endl;

    std::cout << "Testing Matrix -= Matrix (different size) operator" << std::endl;
    caught = false;
    try
    {
        m1 -= m_diff;
    }
    catch (const std::exception &e)
    {
        caught = true;
    }
    assert(caught == true);

    std::cout << "Successfully tested Matrix -= Matrix (different size) operator" << std::endl;

    std::cout << "Testing Matrix + Matrix (same size) operator" << std::endl;
    assert(m1 + m2 == m3);
    std::cout << "Successfully tested Matrix + Matrix (same size) operator" << std::endl;

    std::cout << "Testing Matrix + Matrix (different size) operator" << std::endl;
    caught = false;
    try
    {
        m1 = m1 + m_diff;
    }
    catch (const std::exception &e)
    {
        caught = true;
    }
    assert(caught == true);

    std::cout << "Successfully tested Matrix + Matrix (different size) operator" << std::endl;

    std::cout << "Testing Matrix - Matrix (same size) operator" << std::endl;
    assert(m3 - m2 == m1);
    std::cout << "Successfully tested Matrix - Matrix (same size) operator" << std::endl;

    std::cout << "Testing Matrix - Matrix (different size) operator" << std::endl;
    caught = false;
    try
    {
        m1 = m1 - m_diff;
    }
    catch (const std::exception &e)
    {
        caught = true;
    }
    assert(caught == true);

    std::cout << "Successfully tested Matrix - Matrix (different size) operator" << std::endl;

    return true;
}

bool MatrixTester::test_Multiplication()
{
    size_t rows = 5;
    size_t cols = 4;
    int value = 5;
    int multiplier = 4;
    Matrix m1(rows, cols, value);

    std::cout << "Testing Matrix * int operator" << std::endl;
    Matrix m2 = m1 * multiplier;
    assert(true == this->check_all_elements_equal_value(m2, value * multiplier));
    assert(true == this->check_all_elements_equal_value(m1, value));
    std::cout << "Successfully tested Matrix * int operator" << std::endl;

    std::cout << "Testing Matrix *= int operator" << std::endl;
    m1 *= multiplier;
    assert(true == this->check_all_elements_equal_value(m1, value * multiplier));
    std::cout << "Successfully tested Matrix *= int operator" << std::endl;
    return true;
}

bool MatrixTester::test_Comparison()
{
    size_t rows_1 = 5;
    size_t cols_1 = 4;
    size_t rows_2 = 5;
    size_t cols_2 = 5;
    int value_1 = 1;
    int value_2 = 2;

    Matrix m(rows_1, cols_1, value_1);
    Matrix m_equal(rows_1, cols_1, value_1);
    Matrix m_diff_val(rows_1, cols_1, value_2);
    Matrix m_diff_size(rows_2, cols_2, value_1);

    std::cout << "Testing Matrix == Matrix operator" << std::endl;
    assert((m == m_equal) == true);
    assert((m == m_diff_val) == false);
    assert((m == m_diff_size) == false);
    std::cout << "Successfully tested Matrix == Matrix operator" << std::endl;

    std::cout << "Testing Matrix != Matrix operator" << std::endl;
    assert((m != m_equal) == false);
    assert((m != m_diff_val) == true);
    assert((m != m_diff_size) == true);
    std::cout << "Successfully tested Matrix != Matrix operator" << std::endl;
    return true;
}

bool MatrixTester::test_Constructor_value()
{
    size_t rows = 5;
    size_t cols = 4;
    int value = 4;
    Matrix m(rows, cols, value);
    assert(this->check_all_elements_equal_value(m, value) == true);
    return true;
}

bool MatrixTester::test_Constructor_pointer()
{
    size_t rows = 5;
    size_t cols = 4;
    int value = 4;
    int **data = new int *[rows];
    for (size_t i = 0; i < rows; i++)
    {
        data[i] = new int[cols];
        for (size_t j = 0; j < cols; j++)
        {
            data[i][j] = value;
        }
    }
    Matrix m(rows, cols, data);
    assert(this->check_all_elements_equal_value(m, value) == true);
    return true;
}

bool MatrixTester::test_Constructor_copy()
{
    size_t rows = 5;
    size_t cols = 4;
    int value = 4;
    Matrix m(rows, cols, value);
    Matrix m1(m);
    assert(this->check_all_elements_equal_value(m1, value) == true);
    assert(this->check_all_elements_equal_value(m, value) == true);
    m1[1][2] = 2;
    assert(m[1][2] == value);
    return true;
}

bool MatrixTester::test_printer()
{
    std::string *s_data = new std::string[5];
    s_data[0] = "  0   1   2   3   4 ";
    s_data[1] = "  5   6   7   8   9 ";
    s_data[2] = " 10  11  12  13  14 ";
    s_data[3] = " 15  16  17  18  19 ";
    s_data[4] = " 20  21  22  23  24 ";

    std::cout << "!! Testing ostream << Matrix operation !!" << std::endl;
    std::stringstream ss;
    std::string s;
    size_t rows = 5;
    size_t cols = 5;
    Matrix m(rows, cols);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            m[i][j] = i * cols + j;
        }
    }
    ss << m;
    for (size_t i = 0; i < rows; i++)
    {
        std::getline(ss, s);
        assert(s == s_data[i]);
    }
    std::cout << "!! Successfully tested ostream << Matrix operation !!" << std::endl;
    return true;
}

bool MatrixTester::check_all_elements_equal_value(const Matrix &m, int value)
{
    for (size_t i = 0; i < m.getRows(); i++)
    {
        for (size_t j = 0; j < m.getCols(); j++)
        {
            if (m[i][j] != value)
            {
                return false;
            }
        }
    }
    return true;
}

bool MatrixTester::checkSize(const Matrix &m, size_t rows, size_t cols)
{
    return ((m.getRows() == rows) && (m.getCols() == cols));
}
