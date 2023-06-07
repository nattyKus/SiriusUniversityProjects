#include "parse_arguments.h" 
#include <sstream> 
#include <cstdio>
#include <iostream>

ParseErrors parse_arguments(int argc, char **argv, std::string &filename, double &x, double &y)
{
    static int n = 0;

    n++;
    std::cout << "Function parse_arguments call number " << n << std::endl;
    if (argc < 4)
    {
        return ParseErrors::INSUFFICIENT_ARGUMENTS;
    }
    if (argc > 4)
    {
        return ParseErrors::TO_MUCH_ARGUMENTS;
    }
    filename = std::string(argv[1]);
    
    std::istringstream iss(argv[2]);

    iss >> x;

    if (iss.fail() || (sscanf(argv[3], "%lf", &y) != 1))
    {
        return ParseErrors::NOT_A_NUMBER; 
    }
    return ParseErrors::SUCCESS; 
}

std::string get_error_name(ParseErrors err_info)
{
    switch (err_info) 
    {
        case ParseErrors::INSUFFICIENT_ARGUMENTS:
            return "Not enough arguments";
        case ParseErrors::TO_MUCH_ARGUMENTS:
            return "To much arguments";
        case ParseErrors::NOT_A_NUMBER:
            return "Can not convert input argument to double";
        case ParseErrors::SUCCESS:
            return "No error";
        default:
            return "Unknown error"; 
    }
    return "Unknown error";
}
