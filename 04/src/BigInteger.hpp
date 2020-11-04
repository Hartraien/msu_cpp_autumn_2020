#ifndef __BIGINTEGER_HPP__
#define __BIGINTEGER_HPP__
#include <string>
#include <cstdint>

class BigInteger
{
public:
    //Different constructors
    BigInteger(int64_t);
    BigInteger(const std::string &);
    
    //Destructor
    //Does not delete data if isTemp = true
    //Used in multiply function
    ~BigInteger();

    //Copy Constructor
    BigInteger(const BigInteger &);
    //Move Constructor
    BigInteger(BigInteger &&);

    BigInteger &operator=(const BigInteger &);
    BigInteger &operator=(BigInteger &&);

    //unary minus
    BigInteger operator-() const;

    BigInteger &operator+=(const BigInteger &);
    BigInteger &operator-=(const BigInteger &);
    BigInteger &operator*=(const BigInteger &);

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);
    //Methods for left-sided operations
    friend BigInteger operator+(const BigInteger &, const BigInteger &);
    friend BigInteger operator-(const BigInteger &, const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const BigInteger &);
    //compare operators with same class
    friend bool operator==(const BigInteger &, const BigInteger &);
    friend bool operator!=(const BigInteger &, const BigInteger &);
    friend bool operator<=(const BigInteger &, const BigInteger &);
    friend bool operator>=(const BigInteger &, const BigInteger &);
    friend bool operator<(const BigInteger &, const BigInteger &);
    friend bool operator>(const BigInteger &, const BigInteger &);

    friend bool operator==(int, const BigInteger &);
    friend bool operator!=(int, const BigInteger &);
    friend bool operator<=(int, const BigInteger &);
    friend bool operator>=(int, const BigInteger &);
    friend bool operator<(int, const BigInteger &);
    friend bool operator>(int, const BigInteger &);

    friend bool operator==(const BigInteger &, int);
    friend bool operator!=(const BigInteger &, int);
    friend bool operator<=(const BigInteger &, int);
    friend bool operator>=(const BigInteger &, int);
    friend bool operator<(const BigInteger &, int);
    friend bool operator>(const BigInteger &, int);

protected:
    int32_t compareTo(const BigInteger &) const;
    std::string toString() const;
    BigInteger add(const BigInteger &) const;
    BigInteger subtract(const BigInteger &) const;
    BigInteger multiply(const BigInteger &) const;
    BigInteger shift(size_t) const;

private:
    BigInteger(uint32_t *, size_t);
    BigInteger();
    uint32_t getAt(size_t) const;
    void clearZeros();

private:
    uint32_t *_data;
    bool _sign;
    size_t _length;
    bool isTemp;

    const uint32_t __bitmask = (1 << __bitshift) - 1;
    const uint32_t __digitCount = 4;
    const uint32_t __bitshift = 16;
    const uint32_t __upperBound = 10000;

    enum Signs : bool
    {
        Negative = false,
        Positive = true
    };
};

#endif // __BIGINTEGER_HPP__