#pragma once
#include <cstddef> // size_t declared here
#include <ostream>
#include "Matrix.h"

#ifdef DEBUG
#include <stdexcept> // Exceptions are used only in debug build
#endif

enum class Multiplication
{
    NoTranspose,
    Transpose
};

// Structure implementing matrix as pointer of pointers
class MatrixCSC_CSR : public Matrix
{
    struct Element
    {
        int index;
        
        double value;
        
        inline bool operator<(const Element &e) const { return index < e.index;}
        
        inline bool operator==(const Element &e) const { return index == e.index;}
    };
    private:
        std::vector<int> m_offsets;

        std::vector<Element> m_elements;

        int m_column_number;

        void sort();

        static std::vector<int> read_offsets(int m, std::istream &is);
        
        static std::vector<Element> read_elements(int nz, std::istream &is);
        
        int calc_max_index() const;

        MatrixCSC_CSR() = default;
    
    public:

        MatrixCSC_CSR(int m, int n, std::istream &is);

        inline int row_number() const { return m_offsets.size() - 1;}

        inline int column_number() const { return m_column_number;}

        void matvec(const double *x, double *y, Multiplication mult_type);

        virtual MatrixCSC_CSR& operator+=(const Matrix &o) override;

        inline virtual const int & get_n() const override;
         
        inline virtual const double & get_data(int i, int j) const override; 

        virtual std::vector<double> operator*(const std::vector<double> &o) override;

};