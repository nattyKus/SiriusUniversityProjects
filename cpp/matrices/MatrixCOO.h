#pragma once
#include "Matrix.h"
#include <vector>
#include <istream>
#include <string>
#include <sstream>
#include <algorithm>

class MatrixCOO : public Matrix
{
private:
        std::vector<std::tuple<int, int, double>> m_element;
        int m, n;
        size_t elem_count;

        std::vector<int> read_offsets(int m, std::istream &is);

    public:
        MatrixCOO() = default;
        
        MatrixCOO(int rows_count, int cols_count, std::istream &is);

        void matvec(const double *x, double *y, bool Transpose) const;

        int calc_max_index() const {return n; } ;

        void print_matrix() const;

        void sort() {return; } ;

};