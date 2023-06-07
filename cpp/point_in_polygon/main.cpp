#include "polygon.h"
#include "parse_arguments.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char **argv)
{
    std::string filename;
    double x, y;

    auto err_info = parse_arguments(argc, argv, filename, x, y);

    if (int(err_info) < 0)
    {
        std::cerr << "Error parsing command line arguments: " << get_error_name(err_info) << std::endl;
        return int(err_info);
    }

    std::cout << "Successfully parsed command line, filename = " << filename << ", x = " << x << ", y = " << y << std::endl;

    double point_x = std::atof(argv[2]);
    double point_y = std::atof(argv[3]);
    Point point(point_x, point_y);

    char *input_file = argv[1];
    std::fstream file(input_file);
    if (!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        return -1;
    }

    std::string line;
    std::vector<Point> coords;
    int point_number = 0;

    while(file >> point_x)
    {
        file >> point_y;
        //std::cout << point_x << " " << point_y << std::endl;
        Point polygon_point(point_x, point_y);
        coords.push_back(polygon_point);
        point_number++;
    }

    pointPlace result = point.point_in_polygon(point_number, coords);
    //std::cout << result << std::endl;
    switch (result) 
    {
        case pointPlace::ON_EDGE:
            std::cout << "The point (" << point.X << ", " << point.Y << ") is on the edge of the polygon" << std::endl;
            break;
        case pointPlace::INSIDE:
            std::cout << "The point (" << point.X << ", " << point.Y << ") is inside the polygon" << std::endl;
            break;
        case pointPlace::OUTSIDE:
            std::cout << "The point (" << point.X << ", " << point.Y << ") is outside of the polygon" << std::endl;
            break;
        default:
            break;
    }
    return 0;
}