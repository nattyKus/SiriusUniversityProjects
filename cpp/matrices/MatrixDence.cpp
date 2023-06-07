#include "MatrixDence.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

void MatrixDence::allocate(int N)
{
    // Check matrix sizes
    if (N <= 0)
    {
        std::cerr << "Warning: Matrix sizes are nonpositive, setting them nonpositive one to zero" << std::endl;
    }
    n = std::max(0, N); // set to zero if less then 0, otherwise to N
    data = new double[size_t(n) * size_t(n)]; // allocate array of pointers
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[i * n + j] = rand(); // fill with random values
        }
    }
}

void MatrixDence::deallocate()
{
    delete[] data; // deallocate memory storing pointers to rows
    data = nullptr;
    n = 0;
}

// Constructor
MatrixDence::MatrixDence(int N)
{
    allocate(N);
}

// Destructor
MatrixDence::~MatrixDence()
{
    deallocate();
}

MatrixDence::MatrixDence(const MatrixDence& o)
{
    allocate(o.n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[i * n + j] = o.data[i * n + j];
        }
    }
}
const MatrixDence & MatrixDence::operator=(const MatrixDence &o)
{
    if (n != o.n) // If sizes of do not correspond, free C and allocate with proper sizes
    {
        deallocate();
        allocate(o.n);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[size_t(i) * size_t(n) + j] = o.data[i * n + j];
        }
    }
    return *this;
}

MatrixDence& MatrixDence::operator+=(const Matrix & o)
{
    const MatrixDence *O = dynamic_cast<const MatrixDence *>(&o);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[size_t(i) * size_t(n) + j] += O->data[i * n + j];
        }
    }
    return *this;
}

std::vector<double> MatrixDence::operator*(const std::vector<double> & o)
{
    std::vector<double> matr_mul(n);
    for (int i = 0; i < n; i++)
    {
        matr_mul[i] = 0;
        for (int j = 0; j < n; j++)
        {
            matr_mul[i] += data[size_t(i) * size_t(n) + j] * o[j];
        }
    }
    return matr_mul;
}
