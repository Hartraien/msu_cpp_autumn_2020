#include "Matrix.hpp"

Matrix::Matrix(size_t row_count, size_t col_count, int value)
{
    this->_row_count = row_count;
    this->_col_count = col_count;
    this->_data = new MatrixRow[row_count];
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i].Initialize(this->_col_count, value);
    }
}

Matrix::Matrix(size_t row_count, size_t col_count, int **values)
{
    this->_row_count = row_count;
    this->_col_count = col_count;
    this->_data = new MatrixRow[row_count];
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i].Initialize(this->_col_count, values[i]);
    }
}

Matrix::Matrix(const Matrix &m)
{
    this->_row_count = m._row_count;
    this->_col_count = m._col_count;
    this->_data = new MatrixRow[this->_row_count];
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i].Initialize(m._data[i]);
    }
}

Matrix &Matrix::operator=(const Matrix &m)
{
    if (this == &m)
        return (*this);
    delete _data;
    this->_row_count = m._row_count;
    this->_col_count = m._col_count;
    this->_data = new MatrixRow[this->_row_count];
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i] = m._data[i];
    }
    return (*this);
}

Matrix &Matrix::operator-=(const Matrix &m)
{
    if ((this->_row_count != m._row_count) || (this->_col_count != m._col_count))
        throw std::out_of_range("");
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i] -= m[i];
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
    if ((this->_row_count != m._row_count) || (this->_col_count != m._col_count))
        return false;
    for (size_t i = 0; i < this->_row_count; i++)
    {
        if (this->_data[i] != m._data[i])
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
    size_t maxIntLength = this->maxNumberLength();
    for (size_t i = 0; i < this->_row_count; i++)
    {
        result += this->_data[i].toString(maxIntLength);
        result += "\n";
    }
    return result;
}

Matrix::Matrix(Matrix &&m)
{
    this->_data = m._data;
    this->_row_count = m._row_count;
    this->_col_count = m._col_count;
    m._data = nullptr;
}

size_t Matrix::maxNumberLength() const
{
    size_t maxLength = 0;
    for (size_t i = 0; i < this->_row_count; i++)
    {
        size_t val = this->_data[i].maxNumberLength();
        if (val > maxLength)
            maxLength = val;
    }
    return maxLength + 1;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    os << m.toString();
    return os;
}

const Matrix::MatrixRow &Matrix::operator[](size_t index) const
{
    if (this->_row_count <= index)
        throw std::out_of_range("");
    return this->_data[index];
}

Matrix::MatrixRow &Matrix::operator[](size_t index)
{
    if (this->_row_count <= index)
        throw std::out_of_range("");
    return this->_data[index];
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if ((this->_row_count != m._row_count) || (this->_col_count != m._col_count))
        throw std::out_of_range("");
    Matrix result(*this);
    return result += m;
}

Matrix::~Matrix()
{
    delete[] this->_data;
}

size_t Matrix::getRows() const
{
    return this->_row_count;
}

size_t Matrix::getCols() const
{
    return this->_col_count;
}

Matrix &Matrix::operator*=(int value)
{
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i] *= value;
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
    if ((this->_row_count != m._row_count) || (this->_col_count != m._col_count))
        throw std::out_of_range("");
    for (size_t i = 0; i < this->_row_count; i++)
    {
        this->_data[i] += m[i];
    }
    return (*this);
}
