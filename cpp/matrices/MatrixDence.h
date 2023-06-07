#pragma once
#include <cstddef> // size_t declared here
#include <ostream>
#include "Matrix.h"

#ifdef DEBUG
#include <stdexcept> // Exceptions are used only in debug build
#endif

// Structure implementing matrix as pointer of pointers
class MatrixDence : public Matrix
{
    private:
        int n = 0; // sizes of matrix
        double *data = nullptr; // single pointer to store matrix
        void allocate(int N); // function for calss internal use for memory allocation
        void deallocate(); // function for class internal use for memory deallocation
    public:
        MatrixDence() = default; // Enabling default constructor

        MatrixDence(int n); // Constructor for matrix of given sizes, fills matrix with random elements

        MatrixDence(const MatrixDence & o); // Copy constructor
                                        
        const MatrixDence& operator=(const MatrixDence &); // Assign operator

        virtual ~MatrixDence() override; // Destructor

        inline virtual const int & get_n() const override; // return number of columns 
       
        inline virtual const double & get_data(int i, int j) const override;
        
        virtual MatrixDence& operator+=(const Matrix & o) override;

        virtual std::vector<double> operator*(const std::vector<double> &o) override;

};

const int &MatrixDence::get_n() const
{
    return n;
}

const double &MatrixDence::get_data(int i, int j) const
{
    return data[size_t(i) * size_t(n) + j];
}