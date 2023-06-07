#include "CSR.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    /*
    if (argc < 4) {
        std::cerr << "Wrong number of input arguments" << std::endl;
        return -1;
    }

    char *matrixA = argv[1];
    char *matrixB = argv[2];
    char *output_file = argv[3];

    std::fstream fileA(matrixA);
    std::fstream fileB(matrixB);

    if (!fileA || !fileB)
    {
        std::cerr << "Cannot open file" << std::endl;
        return -1;
    }

     // check shape of matrices
    std::string line;
    std::vector<int> shapeA, shapeB;
    int valueA, valueB;

    std::getline(fileA, line);
    std::istringstream issA(line);
    std::getline(fileB, line);
    std::istringstream issB(line);

    while(issA >> valueA && issB >> valueB){ 
        shapeA.push_back(valueA);
        shapeB.push_back(valueB); 
    }

    int n = shapeA[0];

    if (!(shapeA.size() == 2 && shapeB.size() == 2) || !(shapeA[1] == n && shapeB[0] == n && shapeB[1] == n))
    {
        std::cerr << "Incorrect shape of matrices" << std::endl;
        return -1;
    }
    
    MatrixDence A(n), B(n); // A, B matrices

    auto start = std::chrono::steady_clock::now(); // start time
    A += B; // Matrix sum
    auto end = std::chrono::steady_clock::now(); // end time
    std::cout << "Time Matrix Sum = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1e9 << " seconds" << std::endl; // print elapsed time in seconds
    std::cout << "Matrix sum = " << std::endl << A;
*/
    if (argc < 4) {
        std::cerr << "Wrong number of input arguments" << std::endl;
        return -1;
    }
    std::ifstream ifsA(argv[1]);
    std::ifstream ifsb(argv[2]);
   
    if (!ifsA || !ifsb)
    {
        std::cerr << "Cannot open file" << std::endl;
        return -1;
    }
    std::string line;
    std::getline(ifsA, line);
    int m, n;
    std::istringstream iss(line);
    iss >> m >> n;
    std::getline(ifsA, line);

    typedef float my_float;
    //std::cout << m << ' ' << n << ' ' << line << std::endl;
    CSRMatrix<my_float> A(m, n, ifsA);

    int b_n;
    std::vector<my_float> b;
    my_float value;

    std::getline(ifsA, line);
    std::istringstream issb(line);
    issb >> b_n;

    for (int i; i < b_n; i++)
    {
        std::getline(ifsA, line);
        std::istringstream issb(line);
        issb >> value;
        b.push_back(value);
    }
    std::cout << "Inicialization is successfull" << std::endl;
    std::vector<my_float> x(A.column_number(), 1);
    std::vector<my_float> y1(A.row_number(), 0);
    std::vector<my_float> y2(A.row_number(), 0);

    A.matvec<Multiplication::Transpose>(b.data(), y1.data());

    CSRMatrix<my_float> AAT = A.matmulT(A);

    AAT.matvec<Multiplication::NoTranspose>(x.data(), y2.data());

    std::vector<int> R(y1.size());
    for(size_t i = 0; i < y1.size(); ++i)
        R[i] = y1[i] - y2[i];
    for (auto v: R)
        {
            std::cout << v << ' ';
        }
    std::cout << std::endl;

    /*
    auto B = A + A;
    {
        std::vector<my_float> x(A.column_number(), 1);
        std::vector<my_float> y(A.row_number(), 0);
        A.matvec<Multiplication::NoTranspose>(x.data(), y.data());
        for (auto v: y)
        {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }
    {
        std::vector<my_float> x(A.row_number(), 1);
        std::vector<my_float> y(A.column_number(), 0);
        A.matvec<Multiplication::Transpose>(x.data(), y.data());
        for (auto v: y)
        {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }
    */
    return 0;
}

