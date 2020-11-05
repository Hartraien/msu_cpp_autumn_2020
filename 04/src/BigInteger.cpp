#include "BigInteger.hpp"
BigInteger::BigInteger(int64_t a) : BigInteger()
{
    bool sign = Signs::Positive;
    if (a < 0)
    {
        sign = Signs::Negative;
        a = -a;
    }
    this->_length = 5;
    this->_data = new uint32_t[this->_length];
    for (size_t i = 0; i < this->_length; i++)
    {
        this->_data[i] = a % this->__upperBound;
        a = a / this->__upperBound;
    }
    this->clearZeros();
    this->setSign(sign);
}

BigInteger::BigInteger(const std::string &str) : BigInteger()
{
    bool sign = Signs::Positive;
    std::string buffer;
    auto end = str.rend();
    size_t str_length = str.length() - std::count(str.begin(), str.end(), '_');
    if (str[0] == '-')
    {
        sign = Signs::Negative;
        end -= 1;
        str_length -= 1;
    }
    this->_length = str_length / this->__digitCount;
    if (str_length % this->__digitCount > 0)
    {
        this->_length += 1;
    }
    this->_data = new uint32_t[this->_length];
    size_t counter = 0;
    for (auto rit = str.rbegin(); rit != end; rit++)
    {
        if ((*rit) == '_')
            continue;
        buffer = *rit + buffer;
        if (buffer.length() == this->__digitCount)
        {
            this->_data[counter++] = static_cast<uint32_t>(std::stoul(buffer));
            buffer.clear();
        }
    }
    if (buffer.length() != 0)
    {
        this->_data[counter++] = static_cast<uint32_t>(std::stoul(buffer));
        buffer.clear();
    }
    this->setSign(sign);
}

BigInteger::BigInteger(const BigInteger &b) : BigInteger()
{
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = new uint32_t[this->_length];
    this->isTemp = b.isTemp;
    for (size_t i = 0; i < this->_length; i++)
    {
        this->_data[i] = b._data[i];
    }
}

BigInteger::BigInteger(BigInteger &&b) : BigInteger()
{
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = b._data;
    this->isTemp = b.isTemp;
    b._sign = true;
    b._length = 0;
    b._data = nullptr;
    b.isTemp = false;
}

BigInteger::BigInteger()
{
    this->_data = nullptr;
    this->_sign = Signs::Positive;
    this->_length = 0;
    this->isTemp = false;
}

BigInteger &BigInteger::operator=(const BigInteger &b)
{
    if (this == &b)
        return (*this);
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = new uint32_t[this->_length];
    this->isTemp = b.isTemp;
    for (size_t i = 0; i < this->_length; i++)
    {
        this->_data[i] = b._data[i];
    }
    return (*this);
}

BigInteger &BigInteger::operator=(BigInteger &&b)
{
    if (this == &b)
        return (*this);
    delete[] this->_data;
    this->_sign = b._sign;
    this->_length = b._length;
    this->_data = b._data;
    this->isTemp = b.isTemp;
    b._sign = true;
    b._length = 0;
    b._data = nullptr;
    b.isTemp = false;
    return (*this);
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
    os << b.toString();
    return os;
}

BigInteger BigInteger::operator-() const
{
    BigInteger result(*this);
    result.setSign(!result._sign);
    return result;
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
    for (size_t i = this->_length; i > 0; i--)
    {
        size_t index = i - 1;
        if (this->_data[index] > b._data[index])
            return this->_sign ? 1 : -1;
        else if (this->_data[index] < b._data[index])
            return this->_sign ? -1 : 1;
    }
    return 0;
}

std::string BigInteger::toString() const
{
    std::string result;
    if (this->_length == 0)
        return result;
    for (size_t i = 0; i < this->_length - 1; i++)
    {
        std::string temp = std::to_string(this->_data[i]);
        temp.insert(0, this->__digitCount - temp.length(), '0');
        result = temp + result;
    }
    result = std::to_string(this->_data[this->_length - 1]) + result;
    if (this->_sign == Signs::Negative)
        result = '-' + result;
    return result;
}

BigInteger::BigInteger(uint32_t *data, size_t length) : BigInteger()
{
    this->_data = data;
    this->_length = length;
    this->_sign = Signs::Positive;
    this->isTemp = true;
}

uint32_t BigInteger::getAt(size_t index) const
{
    if (index >= this->_length)
        return 0;
    else
        return this->_data[index];
}

void BigInteger::clearZeros()
{
    size_t newLength = this->_length;
    for (size_t i = this->_length - 1; i > 0; i--)
    {
        if (this->_data[i] == 0)
            newLength = i;
        else
            break;
    }
    uint32_t *temp = new uint32_t[newLength];
    for (size_t i = 0; i < newLength; i++)
    {
        temp[i] = this->_data[i];
    }
    delete[] this->_data;
    this->_data = temp;
    this->_length = newLength;
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
            return b - (-a);
        else
            return a - (-b);
    }
    return a.add(b);
}

BigInteger operator-(const BigInteger &a, const BigInteger &b)
{
    if (a < b)
        return -(b - a);
    if (b._sign == BigInteger::Signs::Negative)
    {
        return a + (-b);
    }
    return a.subtract(b);
}

BigInteger BigInteger::subtract(const BigInteger &b) const
{
    size_t maxLength = (b._length > this->_length ? b._length : this->_length);
    uint32_t carry_over = 0;

    BigInteger result;
    result._sign = this->_sign;
    result._length = maxLength;
    result._data = new uint32_t[result._length];
    for (size_t i = 0; i < maxLength; i++)
    {
        uint32_t left = this->getAt(i);
        uint32_t right = b.getAt(i) + carry_over;
        if (left < right)
        {
            left += result.__upperBound;
            carry_over = 1;
        }
        else
        {
            carry_over = 0;
        }
        uint32_t temp = left - right;
        result._data[i] = temp;
    }
    result.clearZeros();
    result.setSign(this->_sign);
    return result;
}

BigInteger BigInteger::add(const BigInteger &b) const
{
    size_t maxLength = (b._length > this->_length ? b._length : this->_length) + 1;
    uint32_t carry_over = 0;

    BigInteger result;
    result._length = maxLength;
    result._data = new uint32_t[result._length];

    for (size_t i = 0; i < maxLength; i++)
    {
        uint32_t temp = this->getAt(i) + b.getAt(i) + carry_over;
        result._data[i] = temp % result.__upperBound;
        carry_over = temp / result.__upperBound;
    }
    result.clearZeros();
    result.setSign(this->_sign);
    return result;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
    return a.multiply(b);
}

BigInteger BigInteger::multiply(const BigInteger &mult) const
{
    size_t maxIndex = (mult._length > this->_length ? mult._length : this->_length) - 1;

    if (maxIndex == 0)
    {
        BigInteger res = BigInteger(this->getAt(maxIndex) * mult.getAt(maxIndex));
        res.setSign(!(this->_sign ^ mult._sign));
        return res;
    }
    BigInteger result;
    BigInteger a, b, c, d;
    a = BigInteger(this->getAt(maxIndex));
    c = BigInteger(mult.getAt(maxIndex));
    size_t b_length = (maxIndex + 1) > this->_length ? this->_length : maxIndex;
    size_t d_length = (maxIndex + 1) > mult._length ? mult._length : maxIndex;

    b = BigInteger(this->_data, b_length);
    d = BigInteger(mult._data, d_length);

    BigInteger first = a * c;
    BigInteger third = b * d;

    BigInteger second = (a + b) * (c + d) - (first + third);

    result = first.shift(2 * maxIndex) + second.shift(maxIndex) + third;
    result.clearZeros();
    result.setSign(!(this->_sign ^ mult._sign));
    return result;
}

BigInteger BigInteger::shift(size_t sh) const
{
    if (sh == 0)
        return BigInteger(*this);
    BigInteger result;
    result._sign = this->_sign;
    result.isTemp = this->isTemp;
    result._length = this->_length + sh;
    result._data = new uint32_t[result._length];
    for (size_t i = 0; i < sh; i++)
    {
        result._data[i] = 0;
    }
    for (size_t i = sh; i < result._length; i++)
    {
        result._data[i] = this->_data[i - sh];
    }
    return result;
}

void BigInteger::setSign(bool sign)
{
    if ((this->_length == 1) && (this->_data[0] == 0))
        this->_sign = Signs::Positive;
    else
        this->_sign = sign;
}

BigInteger::~BigInteger()
{
    if (this->isTemp == false)
    {
        delete[] this->_data;
    }
}
