#ifndef __BIGINTEGER_HPP__
#define __BIGINTEGER_HPP__
#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>

class BigInteger
{
public:
    // int constructor
    BigInteger(int64_t);
    //string constructor
    //string should contain digits, optional minus sign at the beginning,
    //and optional underscores '_' that can be used to separate digits
    //Examples: 123_456,  -123, -123_456, 123456, 123_____456
    BigInteger(const std::string &);
    //Copy Constructor
    BigInteger(const BigInteger &);
    //Move Constructor
    BigInteger(BigInteger &&);

    //Destructor
    //Does not delete data if isTemp = true
    //(Such BigIntegers are constructed in multiply function by BigInteger(uint32_t *, size_t) constructor, unaccessible outside of class)
    ~BigInteger();

    //Copy-assignment
    //Checks for self-assignment
    BigInteger &operator=(const BigInteger &);
    //Move-assignment
    //Checks for self-assignment
    BigInteger &operator=(BigInteger &&);

    //Converts to string representation
    std::string toString() const;

    //unary minus
    BigInteger operator-() const;

    //Arithmetic operations and assignment
    BigInteger &operator+=(const BigInteger &);
    BigInteger &operator-=(const BigInteger &);
    BigInteger &operator*=(const BigInteger &);

    //Outputs BigInteger to ostream
    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    //Arithmetic operations for when both operands are BigIntegers
    //Supports int arguments through BigInteger(int64_t) conversion
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
    //Compares two BigIntegers: "this" and "arg"
    //Returns -1 if "this"<"arg"
    //         0 if "this" == "arg"
    //         1 if "this" > "arg"
    int32_t compareTo(const BigInteger &) const;

    //Implements addition of "this" and "arg"
    BigInteger add(const BigInteger &) const;
    //Implements subtraction of "arg" from "this"
    BigInteger subtract(const BigInteger &) const;
    //Implements multiplication of "this" and "arg" using Karatsuba algorithm
    BigInteger multiply(const BigInteger &) const;

    //Inserts "arg" zeroes at the beginning of _data
    //Used in multiply method
    BigInteger shift(size_t) const;

    void setSign(bool);

private:
    //Constructs a view of another BigInteger's data with shortened length
    //Used in multiply method
    BigInteger(uint32_t *, size_t);
    //Default constructor, used in other constructors
    BigInteger();
    //Returns element of _data at "index" or 0 if "index" is out of range
    uint32_t getAt(size_t) const;
    //Removes leading zeroes
    //Example: 0_0001 -> 1
    void clearZeros();

private:
    //The number stored. It is stored unsigned, see _sign for sign of number
    uint32_t *_data;
    //Sign of the number
    bool _sign;
    //length of _data
    size_t _length;
    //Whether it points to _data of another BigInteger
    //Such BigIntegers are constructed in multiply function
    bool isTemp;

    //How much digits of number are stored per uint32_t in _data
    //Used in toString() method and BigInteger(string) constructor
    const uint32_t __digitCount = 4;
    //Max value to store in each uint32_t within _data
    //Should be a power of 10 and it's square should be storable in uint32_t
    const uint32_t __upperBound = 10000;

    //Enum for number signs
    enum Signs : bool
    {
        Negative = false,
        Positive = true
    };
};

#endif // __BIGINTEGER_HPP__