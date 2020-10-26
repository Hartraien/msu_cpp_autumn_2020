#include "MatrixTester.hpp"

int main()
{
    size_t cols, rows;
    cols = 5;
    rows = 4;
    Matrix m(rows, cols, 1);
    Matrix n(rows, cols, 2);
    m[1][1] = 4;
    std::cout<<m+n<<std::endl;
}