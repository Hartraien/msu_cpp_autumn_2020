
#include <cassert>
#include <sstream>
#include "BigIntegerTester.hpp"

void BigIntegerTester::test_constructors()
{
    std::cout << "Constructors to be tested:" << std::endl;
    std::cout << "             BigInteger(int64_t)" << std::endl;
    std::cout << "             BigInteger(string)" << std::endl;
    std::cout << "             Copy-constructor" << std::endl;
    std::cout << "             Move-constructor" << std::endl;

    BigInteger intPos(16481);
    BigInteger intNeg(-31233);

    assert(intPos.toString() == "16481");
    assert(intNeg.toString() == "-31233");

    std::cout << "BigInteger(int64_t) tested successfully" << std::endl;

    std::string strPos_data = "3129768";
    std::string strNeg_data = "-3129768";
    std::string strNeg_data_custom = "-3_129_768";
    BigInteger strPos(strPos_data);
    BigInteger strNeg(strNeg_data);

    assert(strPos.toString() == strPos_data);
    assert(strNeg.toString() == strNeg_data);
    assert(strNeg.toString() == BigInteger(strNeg_data_custom).toString());

    std::cout << "BigInteger(string) tested successfully" << std::endl;

    BigInteger copied(strPos);
    assert(copied.toString() == strPos.toString());

    std::cout << "Copy-constructor tested successfully" << std::endl;

    BigInteger moved(std::move(strPos));
    assert(moved.toString() == copied.toString());
    assert(strPos.toString() == "");

    std::cout << "Move-constructor tested successfully" << std::endl
              << std::endl;
}

void BigIntegerTester::test_comparators()
{
    std::cout << "Compare methods to be tested:" << std::endl;
    std::cout << "             operator==" << std::endl;
    std::cout << "             operator!=" << std::endl;
    std::cout << "             operator>" << std::endl;
    std::cout << "             operator<" << std::endl;
    std::cout << "             operator>=" << std::endl;
    std::cout << "             operator<=" << std::endl;

    this->test_comparison_BI_BI();
    this->test_comparison_I_BI();
    this->test_comparison_BI_I();

    std::cout << "Compare methods tested successfully" << std::endl
              << std::endl;
}

void BigIntegerTester::test_arithmetic()
{
    std::cout << "Arithemtic operations to be tested:" << std::endl;
    std::cout << "             operator- (unary)" << std::endl;
    std::cout << "             operator+" << std::endl;
    std::cout << "             operator-" << std::endl;
    std::cout << "             operator*" << std::endl;

    this->test_unary_minus();
    this->test_addition();
    this->test_subtraction();
    this->test_multiplication();

    std::cout << "Arithemtic operations tested successfully" << std::endl
              << std::endl;
}

void BigIntegerTester::test_comparison_BI_BI()
{
    BigInteger first("3213");
    BigInteger second("32__13");

    assert((first >= second) == true);
    assert((first <= second) == true);
    assert((first == second) == true);
    second = BigInteger("3212");
    assert((first != second) == true);
    assert((first < second) == false);
    assert((first <= second) == false);

    second = -second;
    assert((first != second) == true);
    assert((first < second) == false);
    assert((first <= second) == false);
}

void BigIntegerTester::test_comparison_BI_I()
{
    BigInteger first("3213");
    int second = 3213;

    assert((first >= second) == true);
    assert((first <= second) == true);
    assert((first == second) == true);
    second = 3212;
    assert((first != second) == true);
    assert((first < second) == false);
    assert((first <= second) == false);

    second = -3212;
    assert((first != second) == true);
    assert((first < second) == false);
    assert((first <= second) == false);
}

void BigIntegerTester::test_comparison_I_BI()
{
    BigInteger second("3213");
    int first = 3213;

    assert((first >= second) == true);
    assert((first <= second) == true);
    assert((first == second) == true);
    first = 3214;
    assert((first != second) == true);
    assert((first < second) == false);
    assert((first <= second) == false);

    second = -second;
    assert((first != second) == true);
    assert((first < second) == false);
    assert((first <= second) == false);
}

void BigIntegerTester::test_unary_minus()
{
    BigInteger first("3214");
    BigInteger second("0");

    assert((-first).toString() == "-3214");
    assert((-(-first)).toString() == first.toString());

    assert(second == -second);
}

void BigIntegerTester::test_addition()
{
    BigInteger a("20");
    BigInteger b("40");
    assert((a + b) == 60);
    assert((a + b) == (b + a));
    int c = 40;
    assert((a + b) == (c + a));
    assert((a + b) == (a + c));

    a = BigInteger("123456789");
    b = BigInteger("987654321");
    assert((a + b) == BigInteger("1111111110"));

    assert((-a + -b) == BigInteger("-1111111110"));
}

void BigIntegerTester::test_subtraction()
{
    BigInteger a("20");
    BigInteger b("40");
    assert((a - b) == -20);
    assert((b - a) == 20);
    int c = 40;
    assert((b - a) == (c - a));
    assert((a - b) == (a - c));

    a = BigInteger("123456789");
    b = BigInteger("987654321");
    assert((a - b) == BigInteger("-864197532"));
    assert((b - a) == -(a - b));
}

void BigIntegerTester::test_multiplication()
{
    BigInteger a("20");
    BigInteger b("40");
    assert((a * b) == 800);
    assert((a * b) == (b * a));
    int c = 40;
    assert((a * b) == (c * a));
    assert((a * b) == (a * c));

    a = BigInteger("123456789");
    b = BigInteger("987654321");
    assert((a * b) == BigInteger("121932631112635269"));
    assert((a * -b) == BigInteger("-121932631112635269"));
}
