#include "Matrix.hpp"

Matrix::Matrix(size_t row_count, size_t col_count, int value = 0)
{
    this->row_count = row_count;
    this->col_count = col_count;
    this->data = new MatrixRow[row_count];
    for (size_t i = 0; i < this->row_count; i++)
    {
        this->data[i].Initialize(this->col_count, value);
    }
}

Matrix::Matrix(size_t row_count, size_t col_count, int *values)
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
}

Matrix::~Matrix()
{
    delete this->data;
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
}

Matrix& Matrix::operator*(int) const
{
       
}