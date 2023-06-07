#include "MatrixCSC_CSR.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

MatrixCSC_CSR::MatrixCSC_CSR(int m, int n, std::istream &is):
    m_offsets(read_offsets(m, is)),
    m_elements(read_elements(m_offsets[m], is))
{
    
    if (calc_max_index() >= n)
    {
        throw std::runtime_error("Matrix has columns with indexes larger than number of columns");
    }
    m_column_number = n;
    sort();
}

std::vector<int> MatrixCSC_CSR::read_offsets(int m, std::istream &is)
{
    std::string line;
    std::getline(is, line);
    std::istringstream line_stream(std::move(line));
    std::vector<int> offsets(m + 1);
    for (auto& offset: offsets)
    {
        line_stream >> offset;
        if (line_stream.fail())
        {
            throw std::runtime_error("Cannot read enough offsets");
        }
    }
    if (int tmp; (line_stream >> tmp, !line_stream.fail()))
    {
        throw std::runtime_error("To much offsets");
    }
    if (!(line_stream.eof()))
    {
        throw std::runtime_error("Offsets string has some other info");
    }
    if (offsets[0] != 0)
    {
        throw std::runtime_error("First offset is not zero");
    }
    if (!std::is_sorted(offsets.begin(), offsets.end()))
    {
        throw std::runtime_error("Offsets are not sorted");
    }
    return offsets;
}

std::vector</*typename*/ MatrixCSC_CSR::Element > MatrixCSC_CSR::read_elements(int nz, std::istream &is)
{
    std::vector<Element> elements(nz);
    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream(std::move(line));
        for (auto& element: elements)
        {
            line_stream >> element.index;
            if (line_stream.fail())
            {
                throw std::runtime_error("Cannot read enough indexes");
            }
            if (element.index < 0)
            {
                throw std::runtime_error("Negative column number");
            }
        }
        if (int tmp; (line_stream >> tmp, !line_stream.fail()))
        {
            throw std::runtime_error("To much indexes");
        }
        if (!(line_stream.eof()))
        {
            throw std::runtime_error("Indexes string has some other info");
        }
    }
    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream(std::move(line));
        for (auto& element: elements)
        {
            line_stream >> element.value;
            if (line_stream.fail())
            {
                throw std::runtime_error("Cannot read enough values");
            }
        }
        if (int tmp; (line_stream >> tmp, !line_stream.fail()))
        {
            throw std::runtime_error("To much values");
        }
        if (!(line_stream.eof()))
        {
            throw std::runtime_error("Values string has some other info");
        }
    }
    return elements;
}

int MatrixCSC_CSR::calc_max_index() const
{
    int max = 0;
    for (auto & element : m_elements)
    {
        max = std::max(element.index, max);
    }
    return max;
}

void MatrixCSC_CSR::sort()
{
    for (int i = 0; i < row_number(); i++)
    {
        auto start = m_elements.begin() + m_offsets[i];
        auto end = m_elements.begin() + m_offsets[i + 1];
        if (!std::is_sorted(start, end))
        {
            std::sort(start, end);
        }
        if (std::unique(start, end) != end)
        {
            throw std::runtime_error("Two elements with the same index in same vector");
        }
    }
}

void MatrixCSC_CSR::matvec(const double *x, double *y, Multiplication mult_type)
{
    for (int i = 0; i < row_number(); i++)
    {
        auto start = m_elements.begin() + m_offsets[i];
        auto end = m_elements.begin() + m_offsets[i + 1];
        for (; start < end; ++start)
        {
            const int& j = start->index;
            const double& a = start->value;
            if (mult_type == Multiplication::NoTranspose)
            {
                y[i] += a * x[j];
            }
            else
            {
                y[j] += a * x[i];
            }
        }
    }
}

MatrixCSC_CSR& MatrixCSC_CSR::operator+=(const Matrix &o)
{
    /*if (column_number() != o.column_number() || row_number() != o.row_number())
    {
        throw std::runtime_error("Can not sum matrices of different sizes");
    }*/
    const MatrixCSC_CSR *O = dynamic_cast<const MatrixCSC_CSR *>(&o);
    
    MatrixCSC_CSR S;
    S.m_column_number = m_column_number;
    S.m_offsets.resize(O->m_offsets.size(), 0);
    for (int i = 0; i < row_number(); i++)
    {
        auto start_t = m_elements.begin() + m_offsets[i];
        auto end_t = m_elements.begin() + m_offsets[i + 1];
        auto start_o = O->m_elements.begin() + O->m_offsets[i];
        auto end_o = O->m_elements.begin() + O->m_offsets[i + 1];
        while (start_t < end_t && start_o < end_o)
        {
            while (start_t < end_t && *start_t < *start_o)
            {
                S.m_elements.push_back(*start_t);
                S.m_offsets[i + 1]++;
                ++start_t;
            }
            while (start_t < end_t && start_o < end_o && *start_t == *start_o)
            {
                Element t = *start_t;
                t.value += start_o->value;
                S.m_elements.push_back(t);
                S.m_offsets[i + 1]++;
                ++start_t;
                ++start_o;
            }
            if (start_t == end_t) break;
            while (start_o < end_o && *start_o < *start_t)
            {
                S.m_elements.push_back(*start_o);
                S.m_offsets[i + 1]++;
                ++start_o;
            }
        }
        while (start_t < end_t)
        {
            S.m_elements.push_back(*start_t);
            S.m_offsets[i + 1]++;
            ++start_t;
        }
        while (start_o < end_o)
        {
            S.m_elements.push_back(*start_o);
            S.m_offsets[i + 1]++;
            ++start_o;
        }
        S.m_offsets[i + 1] += S.m_offsets[i];
    }
    *this = S;
    return *this;
}