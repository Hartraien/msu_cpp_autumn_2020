#ifndef __BIGINTEGER_HPP__
#define __BIGINTEGER_HPP__
#include <string>
#include <cstdint>

class BigInteger
{
public:
    //Different constructors
    BigInteger(int64_t);
    BigInteger(uint64_t);
    BigInteger(const std::string &);

    //Copy Constructor
    BigInteger(const BigInteger &);
    //Move Constructor
    BigInteger(BigInteger &&);

    //unary minus
    BigInteger operator-();

    BigInteger &operator+=(const BigInteger &);
    BigInteger &operator-=(const BigInteger &);
    BigInteger &operator*=(const BigInteger &);

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);
    //Methods for left-sided operations
    friend BigInteger operator+(const BigInteger &, const BigInteger &);
    friend BigInteger operator-(const BigInteger &, const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const BigInteger &);
    //compare operators
    friend bool operator==(const BigInteger &, const BigInteger &);
    friend bool operator!=(const BigInteger &, const BigInteger &);
    friend bool operator<=(const BigInteger &, const BigInteger &);
    friend bool operator>=(const BigInteger &, const BigInteger &);
    friend bool operator<(const BigInteger &, const BigInteger &);
    friend bool operator>(const BigInteger &, const BigInteger &);

protected:
    int32_t compareTo(const BigInteger &);
    std::string toString();

private:
    BigInteger(uint32_t *, size_t);

private:
    uint32_t *_data;
    bool sign;
    size_t length;

    const uint32_t bitmask = (1 << 16) - 1;
};

#endif // __BIGINTEGER_HPP__