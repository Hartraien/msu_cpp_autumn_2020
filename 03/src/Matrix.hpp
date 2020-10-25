#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <string>
#include <stdexcept>
//#include "MatrixRow.hpp"

class Matrix
{
protected:
    class MatrixRow
    {
    public:
        MatrixRow();
        MatrixRow(size_t, int);
        MatrixRow(size_t, int *);
        MatrixRow(const MatrixRow &);
        MatrixRow &operator=(const MatrixRow &);
        MatrixRow(MatrixRow &&);
        ~MatrixRow();
        void Initialize(size_t, int);
        void Initialize(size_t, int *);
        void Initialize(const MatrixRow &);

        const int operator[](size_t) const;
        int &operator[](size_t);

        MatrixRow &operator*=(int);
        MatrixRow operator*(int) const;

        // for matrix multiplication
        // multiplies per element and sums results
        //int operator*(const MatrixRow &) const;

        MatrixRow &operator+=(const MatrixRow &);
        MatrixRow operator+(const MatrixRow &) const;

        MatrixRow &operator-=(const MatrixRow &);
        MatrixRow operator-(const MatrixRow &) const;

        bool operator==(const MatrixRow &) const;
        bool operator!=(const MatrixRow &) const;

        std::string toString();

    private:
        int *_data;
        size_t length;
        bool isInitialized;
    };

public:
    Matrix(size_t, size_t, int);
    Matrix(size_t, size_t, int *);
    //Matrix(size_t, size_t, MatrixRow *);
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    Matrix &operator=(const Matrix &);
    ~Matrix();

    size_t getRows() const;
    size_t getCols() const;

    Matrix &operator*=(int);
    Matrix operator*(int) const;

    //probably Ignore
    //Matrix &operator*=(const Matrix &);
    //Matrix &operator*(const Matrix &) const;

    Matrix &operator+=(const Matrix &);
    Matrix operator+(const Matrix &) const;

    Matrix &operator-=(const Matrix &);
    Matrix operator-(const Matrix &) const;

    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;

    MatrixRow &operator[](size_t);
    const MatrixRow &operator[](size_t) const;

    void transpose();

    Matrix &getTranspose() const;

    friend std::ostream &operator<<(std::ostream &, const Matrix &);

private:
    std::string toString() const;
    Matrix(size_t, size_t, MatrixRow *);

private:
    //TODO
    // Remake into linear storage with steps
    // To easier transpose function
    MatrixRow *data;
    size_t row_count;
    size_t col_count;
};

#endif // __MATRIX_HPP__