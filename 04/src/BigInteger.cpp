#include "BigInteger.hpp"
BigInteger::BigInteger(int64_t a) : BigInteger()
{
    bool sign = Signs::Positive;
    if (a < 0)
    {
        sign = Signs::Negative;
        a = -a;
    }
    this->length_ = 5;
    this->data_ = new uint32_t[this->length_];
    for (size_t i = 0; i < this->length_; i++)
    {
        this->data_[i] = a % this->upperBound__;
        a = a / this->upperBound__;
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
    this->length_ = str_length / this->digitCount__;
    if (str_length % this->digitCount__ > 0)
    {
        this->length_ += 1;
    }
    this->data_ = new uint32_t[this->length_];
    size_t counter = 0;
    for (auto rit = str.rbegin(); rit != end; rit++)
    {
        if ((*rit) == '_')
            continue;
        buffer = *rit + buffer;
        if (buffer.length() == this->digitCount__)
        {
            this->data_[counter++] = static_cast<uint32_t>(std::stoul(buffer));
            buffer.clear();
        }
    }
    if (buffer.length() != 0)
    {
        this->data_[counter++] = static_cast<uint32_t>(std::stoul(buffer));
        buffer.clear();
    }
    this->setSign(sign);
}

BigInteger::BigInteger(const BigInteger &b) : BigInteger()
{
    this->sign_ = b.sign_;
    this->length_ = b.length_;
    this->data_ = new uint32_t[this->length_];
    this->isTemp_ = b.isTemp_;
    for (size_t i = 0; i < this->length_; i++)
    {
        this->data_[i] = b.data_[i];
    }
}

BigInteger::BigInteger(BigInteger &&b) : BigInteger()
{
    this->sign_ = b.sign_;
    this->length_ = b.length_;
    this->data_ = b.data_;
    this->isTemp_ = b.isTemp_;
    b.sign_ = true;
    b.length_ = 0;
    b.data_ = nullptr;
    b.isTemp_ = false;
}

BigInteger::BigInteger()
{
    this->data_ = nullptr;
    this->sign_ = Signs::Positive;
    this->length_ = 0;
    this->isTemp_ = false;
}

BigInteger &BigInteger::operator=(const BigInteger &b)
{
    if (this == &b)
        return (*this);
    delete[] this->data_;
    this->sign_ = b.sign_;
    this->length_ = b.length_;
    this->data_ = new uint32_t[this->length_];
    this->isTemp_ = b.isTemp_;
    for (size_t i = 0; i < this->length_; i++)
    {
        this->data_[i] = b.data_[i];
    }
    return (*this);
}

BigInteger &BigInteger::operator=(BigInteger &&b)
{
    if (this == &b)
        return (*this);
    delete[] this->data_;
    this->sign_ = b.sign_;
    this->length_ = b.length_;
    this->data_ = b.data_;
    this->isTemp_ = b.isTemp_;
    b.sign_ = true;
    b.length_ = 0;
    b.data_ = nullptr;
    b.isTemp_ = false;
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
    result.setSign(!result.sign_);
    return result;
}

BigInteger &BigInteger::operator+=(const BigInteger &b)
{
    (*this) = (*this) + b;
    return (*this);
}

int32_t BigInteger::compareTo(const BigInteger &b) const
{
    if (this->sign_ != b.sign_)
    {
        if (this->sign_ == Signs::Positive)
            return 1;
        else
            return -1;
    }
    if (this->length_ != b.length_)
    {
        if (this->length_ > b.length_)
            return this->sign_ ? 1 : -1;
        else
            return this->sign_ ? -1 : 1;
    }
    for (size_t i = this->length_; i > 0; i--)
    {
        size_t index = i - 1;
        if (this->data_[index] > b.data_[index])
            return this->sign_ ? 1 : -1;
        else if (this->data_[index] < b.data_[index])
            return this->sign_ ? -1 : 1;
    }
    return 0;
}

std::string BigInteger::toString() const
{
    std::string result;
    if (this->length_ == 0)
        return result;
    for (size_t i = 0; i < this->length_ - 1; i++)
    {
        std::string temp = std::to_string(this->data_[i]);
        temp.insert(0, this->digitCount__ - temp.length(), '0');
        result = temp + result;
    }
    result = std::to_string(this->data_[this->length_ - 1]) + result;
    if (this->sign_ == Signs::Negative)
        result = '-' + result;
    return result;
}

BigInteger::BigInteger(uint32_t *data, size_t length) : BigInteger()
{
    this->data_ = data;
    this->length_ = length;
    this->sign_ = Signs::Positive;
    this->isTemp_ = true;
}

uint32_t BigInteger::getAt(size_t index) const
{
    if (index >= this->length_)
        return 0;
    else
        return this->data_[index];
}

void BigInteger::clearZeros()
{
    size_t newLength = this->length_;
    for (size_t i = this->length_ - 1; i > 0; i--)
    {
        if (this->data_[i] == 0)
            newLength = i;
        else
            break;
    }
    uint32_t *temp = new uint32_t[newLength];
    for (size_t i = 0; i < newLength; i++)
    {
        temp[i] = this->data_[i];
    }
    delete[] this->data_;
    this->data_ = temp;
    this->length_ = newLength;
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
    if (a.sign_ != b.sign_)
    {
        if (a.sign_ == BigInteger::Signs::Negative)
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
    if (b.sign_ == BigInteger::Signs::Negative)
    {
        return a + (-b);
    }
    return a.subtract(b);
}

BigInteger BigInteger::subtract(const BigInteger &b) const
{
    size_t maxLength = (b.length_ > this->length_ ? b.length_ : this->length_);
    uint32_t carry_over = 0;

    BigInteger result;
    result.sign_ = this->sign_;
    result.length_ = maxLength;
    result.data_ = new uint32_t[result.length_];
    for (size_t i = 0; i < maxLength; i++)
    {
        uint32_t left = this->getAt(i);
        uint32_t right = b.getAt(i) + carry_over;
        if (left < right)
        {
            left += result.upperBound__;
            carry_over = 1;
        }
        else
        {
            carry_over = 0;
        }
        uint32_t temp = left - right;
        result.data_[i] = temp;
    }
    result.clearZeros();
    result.setSign(this->sign_);
    return result;
}

BigInteger BigInteger::add(const BigInteger &b) const
{
    size_t maxLength = (b.length_ > this->length_ ? b.length_ : this->length_) + 1;
    uint32_t carry_over = 0;

    BigInteger result;
    result.length_ = maxLength;
    result.data_ = new uint32_t[result.length_];

    for (size_t i = 0; i < maxLength; i++)
    {
        uint32_t temp = this->getAt(i) + b.getAt(i) + carry_over;
        result.data_[i] = temp % result.upperBound__;
        carry_over = temp / result.upperBound__;
    }
    result.clearZeros();
    result.setSign(this->sign_);
    return result;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
    return a.multiply(b);
}

BigInteger BigInteger::multiply(const BigInteger &mult) const
{
    size_t maxIndex = (mult.length_ > this->length_ ? mult.length_ : this->length_) - 1;

    if (maxIndex == 0)
    {
        BigInteger res = BigInteger(this->getAt(maxIndex) * mult.getAt(maxIndex));
        res.setSign(!(this->sign_ ^ mult.sign_));
        return res;
    }
    BigInteger result;
    BigInteger a, b, c, d;
    a = BigInteger(this->getAt(maxIndex));
    c = BigInteger(mult.getAt(maxIndex));
    size_t b_length = (maxIndex + 1) > this->length_ ? this->length_ : maxIndex;
    size_t d_length = (maxIndex + 1) > mult.length_ ? mult.length_ : maxIndex;

    b = BigInteger(this->data_, b_length);
    d = BigInteger(mult.data_, d_length);

    BigInteger first = a * c;
    BigInteger third = b * d;

    BigInteger second = (a + b) * (c + d) - (first + third);

    result = first.shift(2 * maxIndex) + second.shift(maxIndex) + third;
    result.clearZeros();
    result.setSign(!(this->sign_ ^ mult.sign_));
    return result;
}

BigInteger BigInteger::shift(size_t sh) const
{
    if (sh == 0)
        return BigInteger(*this);
    BigInteger result;
    result.sign_ = this->sign_;
    result.isTemp_ = this->isTemp_;
    result.length_ = this->length_ + sh;
    result.data_ = new uint32_t[result.length_];
    for (size_t i = 0; i < sh; i++)
    {
        result.data_[i] = 0;
    }
    for (size_t i = sh; i < result.length_; i++)
    {
        result.data_[i] = this->data_[i - sh];
    }
    return result;
}

void BigInteger::setSign(bool sign)
{
    if ((this->length_ == 1) && (this->data_[0] == 0))
        this->sign_ = Signs::Positive;
    else
        this->sign_ = sign;
}

BigInteger::~BigInteger()
{
    if (this->isTemp_ == false)
    {
        delete[] this->data_;
    }
}
