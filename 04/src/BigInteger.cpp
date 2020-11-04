#include "BigInteger.hpp"
BigInteger::BigInteger(int64_t a) : BigInteger()
{
    if (a < 0)
        this->_sign = Signs::Negative;
    a = -a;
    uint32_t one, two;
    one = static_cast<uint32_t>(a);
    two = static_cast<uint32_t>(a >> 32);
    if (two == 0)
    {
        this->_length = 1;
    }
    else
    {
        this->_length = 2;
    }
    this->_data = new uint32_t[this->_length];
    _data[0] = one;
    if (this->_length == 2)
    {
        _data[1] = two;
    }
}

BigInteger::BigInteger(const std::string &str) : BigInteger()
{
    std::string buffer;
    auto end = str.rend();
    size_t str_length = str.length();
    if (str[0] == '-')
    {
        this->_sign = Signs::Negative;
        end -= 1;
        str_length -= 1;
    }
    this->_length = str_length / this->digitCount;
    if (str_length % this->digitCount > 0)
    {
        this->_length += 1;
    }
    this->_data = new uint32_t[this->_length];
    size_t counter = 0;
    for (std::string::reverse_iterator rit = str.rbegin(); rit != end; rit++)
    {
        buffer += *rit;
        if (buffer.length() == this->digitCount)
        {
            this->_data[counter++] = static_cast<uint32_t>(std::stoul(str));
            buffer.clear();
        }
    }
    if (buffer.length() != 0)
    {
        this->_data[counter++] = static_cast<uint32_t>(std::stoul(str));
        buffer.clear();
    }
}

BigInteger::BigInteger(const BigInteger &b) : BigInteger()
{
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = new uint32_t[this->_length];
    for (size_t i = 0; i < _length; i++)
    {
        this->_data[i] = b._data[i];
    }
}

BigInteger::BigInteger(BigInteger &&b) : BigInteger()
{
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = b._data;
    b._sign = true;
    b._length = 0;
    b._data = nullptr;
}

BigInteger::BigInteger()
{
    this->_data = nullptr;
    this->_sign = Signs::Positive;
    this->_length = 0;
}

BigInteger &BigInteger::operator=(const BigInteger &b)
{
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = new uint32_t[this->_length];
    for (size_t i = 0; i < _length; i++)
    {
        this->_data[i] = b._data[i];
    }
}

BigInteger &BigInteger::operator=(BigInteger &&b)
{
    if (this == &b)
        return;
    delete[] this->_data;
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = b._data;
    b._sign = true;
    b._length = 0;
    b._data = nullptr;
}

BigInteger &BigInteger::operator-=(const BigInteger &b)
{
    (*this) = (*this) - b;
    return (*this);
}

BigInteger &BigInteger::operator*=(const BigInteger &b)
{
    (*this) = (*this) * b;
    return (*this);
}

std::ostream &operator<<(std::ostream &os, const BigInteger &b)
{
    os << b;
    return os;
}

BigInteger BigInteger::operator-() const
{
    BigInteger result(*this);
    if (result != 0)
        result._sign = !result._sign;
    return result;
}

bool operator>(const BigInteger &a, int b)
{
    return (a > BigInteger(b));
}

bool operator<(const BigInteger &a, int b)
{
    return (a < BigInteger(b));
}

bool operator>=(const BigInteger &a, int b)
{
    return (a == BigInteger(b));
}

bool operator<=(const BigInteger &a, int b)
{
    return (a <= BigInteger(b));
}

bool operator!=(const BigInteger &a, int b)
{
    return (a != BigInteger(b));
}

bool operator==(const BigInteger &a, int b)
{
    return (a == BigInteger(b));
}

bool operator>(int a, const BigInteger &b)
{
    return (BigInteger(a) > b);
}

bool operator<(int a, const BigInteger &b)
{
    return (BigInteger(a) < b);
}

bool operator>=(int a, const BigInteger &b)
{
    return (BigInteger(a) >= b);
}

bool operator<=(int a, const BigInteger &b)
{
    return (BigInteger(a) <= b);
}

bool operator!=(int a, const BigInteger &b)
{
    return (BigInteger(a) != b);
}

bool operator==(int a, const BigInteger &b)
{
    return (BigInteger(a) == b);
}

BigInteger &BigInteger::operator+=(const BigInteger &b)
{
    (*this) = (*this) + b;
    return (*this);
}

int32_t BigInteger::compareTo(const BigInteger &b) const
{
    if (this->_sign != b._sign)
    {
        if (this->_sign == Signs::Positive)
            return 1;
        else
            return -1;
    }
    if (this->_length != b._length)
    {
        if (this->_length > b._length)
            return this->_sign ? 1 : -1;
        else
            return this->_sign ? -1 : 1;
    }
    for (size_t i = 0; i < this->_length; i++)
    {
        if (this->_data[i] > b._data[i])
            return this->_sign ? 1 : -1;
        else if (this->_data[i] < b._data[i])
            return this->_sign ? -1 : 1;
    }
    return 0;
}

std::string BigInteger::toString() const
{
    std::string result;
    for (size_t i = 0; i < this->_length; i++)
    {
        result = std::to_string(this->_data[i]) + result;
    }
    if (this->_sign == Signs::Negative)
        result = '-' + result;
    return result;
}

BigInteger::BigInteger(uint32_t *data, size_t length)
{
    this->_data = data;
    this->_length = length;
    this->_sign = Signs::Positive;
}

uint32_t BigInteger::getAt(size_t index)
{
    if (index > this->_length)
        return 0;
    else
        return this->_data[index];
}

bool operator>(const BigInteger &a, const BigInteger &b)
{
    int32_t comp = a.compareTo(b);
    return (comp == 1);
}

bool operator<(const BigInteger &a, const BigInteger &b)
{
    int32_t comp = a.compareTo(b);
    return (comp == -1);
}

bool operator>=(const BigInteger &a, const BigInteger &b)
{
    int32_t comp = a.compareTo(b);
    return (comp != -1);
}

bool operator<=(const BigInteger &a, const BigInteger &b)
{
    int32_t comp = a.compareTo(b);
    return (comp != 1);
}

bool operator!=(const BigInteger &a, const BigInteger &b)
{
    int32_t comp = a.compareTo(b);
    return (comp != 0);
}

bool operator==(const BigInteger &a, const BigInteger &b)
{
    int32_t comp = a.compareTo(b);
    return (comp == 0);
}

BigInteger operator+(const BigInteger &a, const BigInteger &b)
{
    if (a._sign != b._sign)
    {
        if (a._sign == BigInteger::Signs::Negative)
            return b - a;
        else
            return a - b;
    }
    size_t maxLength = b._length > a._length ? b._length : a._length;
    uint32_t carry_over = 0;

    BigInteger result;
    result._sign = a._sign;
    result._length = maxLength;
    result._data = new uint32_t[result._length];

    for (size_t i = 0; i < maxLength; i++)
    {
    }
    return result;
}
