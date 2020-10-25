#include "Matrix.hpp"

Matrix::MatrixRow::MatrixRow()
{
    this->_data = nullptr;
    this->length = 0;
    this->isInitialized = false;
}

Matrix::MatrixRow::MatrixRow(size_t length, int value)
{
    this->_data = new int[length];
    this->length = length;
    this->isInitialized = true;
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] = value;
    }
}

Matrix::MatrixRow::MatrixRow(size_t length, int *data)
{
    this->_data = data;
    this->length = length;
    this->isInitialized = true;
}

Matrix::MatrixRow::MatrixRow(const MatrixRow &r)
{
    this->_data = new int[r.length];
    this->length = r.length;
    this->isInitialized = r.isInitialized;
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] = r[i];
    }
}

Matrix::MatrixRow &Matrix::MatrixRow::operator=(const MatrixRow &r)
{
    delete[] this->_data;
    this->_data = new int[r.length];
    this->length = r.length;
    this->isInitialized = r.isInitialized;
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] = r[i];
    }
    return (*this);
}

Matrix::MatrixRow::MatrixRow(MatrixRow &&r)
{
    this->_data = r._data;
    this->length = r.length;
    this->isInitialized = r.isInitialized;
    r._data = nullptr;
}

Matrix::MatrixRow::~MatrixRow()
{
    delete[] this->_data;
}
void Matrix::MatrixRow::Initialize(size_t length, int value)
{
    delete[] this->_data;
    this->_data = new int[length];
    this->length = length;
    this->isInitialized = true;
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] = value;
    }
}
void Matrix::MatrixRow::Initialize(size_t length, int *data)
{
    delete[] this->_data;
    this->_data = data;
    this->length = length;
    this->isInitialized = true;
}
void Matrix::MatrixRow::Initialize(const MatrixRow &r)
{
    delete[] this->_data;
    this->_data = new int[r.length];
    this->length = r.length;
    this->isInitialized = r.isInitialized;
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] = r[i];
    }
}

const int Matrix::MatrixRow::operator[](size_t index) const
{
    if (this->length <= index)
        throw std::out_of_range("");
    return this->_data[index];
}
int &Matrix::MatrixRow::operator[](size_t index)
{
    if (this->length <= index)
        throw std::out_of_range("");
    return this->_data[index];
}

Matrix::MatrixRow &Matrix::MatrixRow::operator*=(int value)
{
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] *= value;
    }
    return *this;
}

Matrix::MatrixRow Matrix::MatrixRow::operator*(int value) const
{
    Matrix::MatrixRow result(*this);
    return result *= value;
}

Matrix::MatrixRow &Matrix::MatrixRow::operator+=(const MatrixRow &m)
{
    if (this->length != m.length)
        throw std::out_of_range("");
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] += m[i];
    }
    return (*this);
}
Matrix::MatrixRow Matrix::MatrixRow::operator+(const MatrixRow &m) const
{
    MatrixRow result(*this);
    return result += m;
}

Matrix::MatrixRow &Matrix::MatrixRow::operator-=(const MatrixRow &m)
{
    if (this->length != m.length)
        throw std::out_of_range("");
    for (size_t i = 0; i < this->length; i++)
    {
        this->_data[i] -= m[i];
    }
    return (*this);
}

Matrix::MatrixRow Matrix::MatrixRow::operator-(const MatrixRow &m) const
{
    MatrixRow result(*this);
    return result -= m;
}

bool Matrix::MatrixRow::operator==(const MatrixRow &m) const
{
    if (this->length != m.length)
        return false;
    for (size_t i = 0; i < this->length; i++)
    {
        if (this->_data[i] != m[i])
            return false;
    }
    return true;
}
bool Matrix::MatrixRow::operator!=(const MatrixRow &m) const
{
    return !(*this == m);
}

std::string Matrix::MatrixRow::toString()
{
    std::string result = "";
    for (size_t i = 0; i < this->length; i++)
    {
        result += std::to_string(this->_data[i]);
        result += " ";
    }
    return result;
}