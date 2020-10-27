#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <string>
#include <stdexcept>

class Matrix
{
protected:
    // This class represents rows of matrix
    // Since this class should not be instantiated outside of this class, it is declared under 'protected' access specifier
    class MatrixRow
    {
    public:
        //Default constructor
        MatrixRow();
        //Creates MatrixRow of _length size_t with each element equal int
        MatrixRow(size_t, int);
        //Creates MatrixRow from int* of lentgth size_t
        MatrixRow(size_t, int *);

        //Copy constructor
        //Performs deep copy of _data field
        MatrixRow(const MatrixRow &);

        //Performs deep copy of _data field
        MatrixRow &operator=(const MatrixRow &);
        //Move Constructor, does not perform deep copy
        MatrixRow(MatrixRow &&);
        //Destructor
        //Calls delete[] _data
        ~MatrixRow();
        //Sets _data field to size size_t and sets all values to int
        //Used in Matrix constructor of type Matrix(size_t, size_t, int)
        void Initialize(size_t, int);
        //Sets _data field equal to int*
        //Used in Matrix constructor of type Matrix(size_t, size_t, int*)
        void Initialize(size_t, int *);
        //Performs siliar to copy constructor
        //Used in Matrix copy constructor
        void Initialize(const MatrixRow &);

        //Returns value of the element at size_t position (indexing starts with 0)
        //Throws std::out_of_bounds("") execption if size_t index is out of _data bounds
        //Used for rvalue operations
        const int operator[](size_t) const;
        //Returns reference to the element at size_t position (indexing starts with 0)
        //Throws std::out_of_bounds("") execption if size_t index is out of _data bounds
        //Used for assignment
        int &operator[](size_t);

        //Multiplies all elements of this MatrixRow by int and stores result in this MatrixRow
        //Used in Matrix::operator*=
        MatrixRow &operator*=(int);
        //Multiplies all elements of this MatrixRow by int and stores result in new MatrixRow
        //Used in Matrix::operator*
        MatrixRow operator*(int) const;

        //Performs indexwise summation of this MatrixRow and argument MatrixRow and stores result in this MatrixRow
        //Used in Matrix::operator+=
        MatrixRow &operator+=(const MatrixRow &);
        //Performs indexwise summation of this MatrixRow and argument MatrixRow and stores result in new MatrixRow
        //Used in Matrix::operator+
        MatrixRow operator+(const MatrixRow &) const;

        //Performs indexwise subtraction of argument MatrixRow from this MatrixRow and stores result in this MatrixRow
        //Used in Matrix::operator-=
        MatrixRow &operator-=(const MatrixRow &);
        //Performs indexwise subtraction of argument MatrixRow from this MatrixRow and stores result in new MatrixRow
        //Used in Matrix::operator-
        MatrixRow operator-(const MatrixRow &) const;

        //Compares two MatrixRows elementwise
        //Also returns false if this MatrixRows have different _length
        bool operator==(const MatrixRow &) const;
        //Compares two MatrixRows elementwise
        //Also returns false if this MatrixRows have same _length
        bool operator!=(const MatrixRow &) const;

        //Converts MatrixRow to string representation
        //argument - _length of each number string for formatted output
        //Used in Matrix::toString() method
        std::string toString(size_t) const;

        //Returns _length of longest number in MatrixRow
        //Used in Matrix::maxNumberLength() method
        size_t maxNumberLength() const;

    private:
        int *_data;
        size_t _length;
    };

public:
    //Constructs Matrix with all elements equal to value
    //If value is not specified, all elements are set to 0
    Matrix(size_t, size_t, int = 0);
    //Construct Matrix from two-dimensional array
    Matrix(size_t, size_t, int **);
    //Copy Constructor, performs deep copy
    Matrix(const Matrix &);
    //Move constuctor
    Matrix(Matrix &&);
    //Performs deep copy
    Matrix &operator=(const Matrix &);
    //Destructor
    //Calls delete[] _data
    ~Matrix();

    //Returns number of rows in Matrix
    size_t getRows() const;
    //Returns number of columns in Matrix
    size_t getCols() const;

    //Multiplies all elements of this Matrix by int and stores result in this Matrix
    Matrix &operator*=(int);
    //Multiplies all elements of this Matrix by int and stores result in new Matrix
    Matrix operator*(int) const;

    //Performs indexwise summation of this Matrix and argument Matrix and stores result in this Matrix
    //Throws std::out_of_bounds("") if sizes of Matrices do not match
    Matrix &operator+=(const Matrix &);
    //Performs indexwise summation of this Matrix and argument Matrix and stores result in new Matrix
    //Throws std::out_of_bounds("") if sizes of Matrices do not match
    Matrix operator+(const Matrix &) const;

    //Performs indexwise subtraction of argument Matrix from this Matrix and stores result in this Matrix
    //Throws std::out_of_bounds("") if sizes of Matrices do not match
    Matrix &operator-=(const Matrix &);
    //Performs indexwise subtraction of argument Matrix from this Matrix and stores result in new Matrix
    //Throws std::out_of_bounds("") if sizes of Matrices do not match
    Matrix operator-(const Matrix &) const;

    //Compares two Matrix elementwise
    //Also returns false if Matrices are of different sizes
    bool operator==(const Matrix &) const;
    //Compares two Martrix elementwise
    //Also returns true if Matrices are of different sizes
    bool operator!=(const Matrix &) const;

    //Returns reference to the MatrixRow at size_t position (indexing starts with 0)
    //Throws std::out_of_bounds("") execption if size_t index is out of _data bounds
    //Used for assignment
    MatrixRow &operator[](size_t);
    //Returns MatrixRow at size_t position (indexing starts with 0)
    //Throws std::out_of_bounds("") execption if size_t index is out of _data bounds
    //Used for rvalue operations
    const MatrixRow &operator[](size_t) const;

    //Prints Matrix to std::ostream
    friend std::ostream &operator<<(std::ostream &, const Matrix &);

private:
    //Converts Matrix to string representation
    std::string toString() const;
    //Returns _length of largest (by absolute value) number in Matrix for formatted string representation
    //Also saves one place for minus sign
    size_t maxNumberLength() const;

private:
    MatrixRow *_data;
    size_t _row_count;
    size_t _col_count;
};

#endif // __MATRIX_HPP__