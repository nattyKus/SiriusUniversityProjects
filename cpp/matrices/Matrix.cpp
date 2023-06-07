#include "Matrix.h"
#include <ostream>
#include <iomanip>
std::ostream & operator<<(std::ostream & os, const Matrix &A)
{
    for (int i = 0; i < A.get_n(); i++)
    {
        for (int j = 0; j < A.get_n(); j++)
        {
            os << std::setw(7) << std::setprecision(2) << A.get_data(i, j) << ' ';
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}
