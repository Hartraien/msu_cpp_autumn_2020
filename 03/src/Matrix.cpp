#include "Matrix.hpp"

Matrix::Matrix(size_t row_count, size_t col_count, int value)
{
    this->row_count = row_count;
    this->col_count = col_count;
    this->data = new MatrixRow[row_count];
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i].Initialize(this->col_count, value);
    }
}

Matrix::Matrix(size_t row_count, size_t col_count, int **values)
{
    this->row_count = row_count;
    this->col_count = col_count;
    this->data = new MatrixRow[row_count];
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i].Initialize(this->col_count, values[i]);
    }
}

Matrix::Matrix(const Matrix &m)
{
    this->row_count = m.row_count;
    this->col_count = m.col_count;
    this->data = new MatrixRow[this->row_count];
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i].Initialize(m.data[i]);
    }
}

Matrix &Matrix::operator=(const Matrix &m)
{
    delete data;
    this->row_count = m.row_count;
    this->col_count = m.col_count;
    this->data = new MatrixRow[this->row_count];
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i] = m.data[i];
    }
    return (*this);
}

Matrix &Matrix::operator-=(const Matrix &m)
{
    if ((this->row_count != m.row_count) || (this->col_count != m.col_count))
        throw std::out_of_range("");
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i] -= m[i];
    }
    return (*this);
}

Matrix Matrix::operator-(const Matrix &m) const
{
    Matrix result(*this);
    return result -= m;
}

bool Matrix::operator==(const Matrix &m) const
{
    if ((this->row_count != m.row_count) || (this->col_count != m.col_count))
        return false;
    for (size_t i = 0; i < this->row_count; i++)
    {
        if (this->data[i] != m.data[i])
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix &m) const
{
    return !(*this == m);
}

std::string Matrix::toString() const
{
    std::string result = "";
    size_t maxIntLength = this->findNumberLength();
    for (size_t i = 0; i < this->row_count; i++)
    {
        result += this->data[i].toString(maxIntLength);
        result += "\n";
    }
    return result;
}

Matrix::Matrix(Matrix &&m)
{
    this->data = m.data;
    this->row_count = m.row_count;
    this->col_count = m.col_count;
    m.data = nullptr;
}

size_t Matrix::findNumberLength() const
{
    size_t maxLength = 0;
    for (size_t i =0; i <this->row_count; i++)
    {
        size_t val = this->data[i].findNumberLength();
        if(val>maxLength)
            maxLength = val;
    }
    return maxLength+1;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    os << m.toString();
    return os;
}

const Matrix::MatrixRow &Matrix::operator[](size_t index) const
{
    if (this->row_count <= index)
        throw std::out_of_range("");
    return this->data[index];
}

Matrix::MatrixRow &Matrix::operator[](size_t index)
{
    if (this->row_count <= index)
        throw std::out_of_range("");
    return this->data[index];
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if ((this->row_count != m.row_count) || (this->col_count != m.col_count))
        throw std::out_of_range("");
    Matrix result(*this);
    return result += m;
}

Matrix::~Matrix()
{
    delete[] this->data;
}

size_t Matrix::getRows() const
{
    return this->row_count;
}

size_t Matrix::getCols() const
{
    return this->col_count;
}

Matrix &Matrix::operator*=(int value)
{
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i] *= value;
    }
    return (*this);
}

Matrix Matrix::operator*(int value) const
{
    Matrix result(*this);
    return result *= value;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
    if ((this->row_count != m.row_count) || (this->col_count != m.col_count))
        throw std::out_of_range("");
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i] += m[i];
    }
    return (*this);
}

