#pragma once
#include <ostream>
#include <vector>

// Structure implementing matrix as pointer of pointers
class Matrix
{
    public:
        virtual ~Matrix() = default; // Destructor

        //virtual const int & get_m() const = 0; // return number of rows, inline means implemented in header, last const means that object is not modified

        virtual const int & get_n() const = 0; // return number of columns

        virtual const double & get_data(int i, int j) const = 0;  

        virtual Matrix& operator+=(const Matrix & o) = 0;
        
        virtual std::vector<double> operator*(const std::vector<double> & o) = 0;
};

std::ostream & operator<<(std::ostream & os, const Matrix &);

