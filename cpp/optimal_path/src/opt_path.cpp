#include <iostream>
#include "../load_png/lodepng.h"
#include <vector>
#include <cstdint>
#include <string>
#include <iterator>
#include <algorithm>
#include "../src/opt_path.h"


void decodeFromPng(std::vector<unsigned char>& image, const char* filename, unsigned height, unsigned width) {
    /*
     * Функция для чтения png файла
     */
    std::vector<unsigned char> png;
    //load and decode
    unsigned error = lodepng::load_file(png, filename);
    if(!error) error = lodepng::decode(image, width, height, png);

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ... 
}

void getBlueChannel(const std::vector<unsigned char>& image, int** arr, int rows, int cols) {
    /*
     * Функция, которая выделяет синий канал из одномерного вектора и
     * заполняет им двумерный массив
     */
    for (int i = 2, j = 0, k = 0; i < image.size(); i += 4, ++k) {
        if (k == cols) {
            k = 0; // обнуляем номер столбца
            ++j; // увеличиваем номер строки
        }
        arr[j][k] = int(image[i]);
        
    }
}
void printArray(int** arr, int rows, int cols) { 
    /*
     * Функция для вывода массива в консоль
     */
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            std::cout << arr[i][j] << " ";
        std::cout << std::endl;    
    }
}

void drawPath(const std::vector<int>& path, std::vector<unsigned char>& image, int rows, int cols, const char* output_file) {
    int i = 0, j = -1;
    int previousPoint = -1;
    for (auto& e : path) {
        if (previousPoint == e)
            ++i;
        else
            j = e;
        previousPoint = e;
        // draw red path R = 255, G = 0, B = 0
        int index = (i*cols + j)*4;
        image[index] = (unsigned char)255;
        image[++index] = (unsigned char)0;
        image[++index] = (unsigned char)0;
    }


    
    //Encode the image
    unsigned error = lodepng::encode(output_file, image, cols, rows);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void evalOptimalPath(int x, int y, int x_finish, int y_finish, int** opt_path, int** arr, int rows, int columns, int** shortest_path)
{
    if (y != y_finish || x != x_finish)
    {
        std::cout << y << " " << x << std::endl;
        int left_point_x, right_point_x, down_point_y, new_path;
        bool left_path_available, right_path_available, down_path_available = false;
        if (x - 1 >= 0) 
        {
            left_point_x = x - 1;
            new_path = opt_path[y][x] + arr[y][left_point_x];
            if (new_path < opt_path[y][left_point_x]) 
            {
                std::cout << "Left path exist" << std::endl;
                std::cout << "path_value = " << new_path << std::endl;
                opt_path[y][left_point_x] = new_path;
                left_path_available = true;
                shortest_path[y*rows + left_point_x][0] = y;
                shortest_path[y*rows + left_point_x][1] = x;
            }
        }
        if (x + 1 < columns) 
        {
            right_point_x = x + 1;
            new_path = opt_path[y][x] + arr[y][right_point_x];
            if (new_path < opt_path[y][right_point_x]) 
            {
                std::cout << "Right path exist" << std::endl;
                std::cout << "path_value = " << new_path << std::endl;
                opt_path[y][right_point_x] = new_path;
                right_path_available = true;
                shortest_path[y*rows + right_point_x][0] = y;
                shortest_path[y*rows + right_point_x][1] = x;
            }
        }
        if (y + 1 < rows) 
        {
            down_point_y = y + 1;
            new_path = opt_path[y][x] + arr[down_point_y][x];
            if (new_path < opt_path[down_point_y][x])
            {
                std::cout << "Down path exist" << std::endl;
                std::cout << "path_value = " << new_path << std::endl;
                opt_path[down_point_y][x] = new_path;
                down_path_available = true;
                shortest_path[down_point_y*rows + x][0] = y;
                shortest_path[down_point_y*rows + x][1] = x;
            }
        }
        /*
        std::vector<int> points;
        if (left_path_available) points.push_back(opt_path[down_point_y][x]);
        if (right_path_available) points.push_back(opt_path[y][left_point_x]);
        if (down_path_available) points.push_back(opt_path[y][right_point_x]);
           
        std::sort(points.begin(), points.end());
        */
        
        if (left_path_available)
        {
            if (right_path_available)
            {
                if (down_path_available)
                {
                    if (opt_path[down_point_y][x] < opt_path[y][right_point_x] 
                        && opt_path[down_point_y][x] < opt_path[y][left_point_x])
                    {
                        evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        if (opt_path[y][left_point_x] < opt_path[y][right_point_x])
                        {
                            evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                            evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        } 
                        else 
                        {
                            evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                            evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        }
                    }
                    else if ((opt_path[y][right_point_x] < opt_path[y][left_point_x]) &&
                            (opt_path[y][right_point_x] < opt_path[down_point_y][x]))
                    {
                        evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        if (opt_path[down_point_y][x] < opt_path[y][left_point_x])
                        {
                            evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                            evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        }
                        else
                        {
                            evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                            evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        }
                    }
                    else 
                    {
                        evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        if (opt_path[down_point_y][x] < opt_path[y][right_point_x])
                        {
                            evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                            evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        }
                        else
                        {
                            evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                            evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                        }
                    }
                }
                else if (opt_path[y][left_point_x] < opt_path[y][right_point_x])
                {
                    evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                    evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                } 
                else 
                {
                    evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                    evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                }
            }
            else if (down_path_available)
            {
                if (opt_path[y][left_point_x] < opt_path[down_point_y][x])
                {
                    evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                    evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                } 
                else 
                {
                    evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                    evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                }
            }
            else evalOptimalPath(left_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
        }
        else if (down_path_available)
        {
            if (right_path_available)
            {
                if (opt_path[y][right_point_x] < opt_path[down_point_y][x])
                {
                    evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                    evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                } 
                else 
                {
                    evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                    evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
                }
            } 
            else evalOptimalPath(x, down_point_y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
        }
        else if (right_path_available)
            evalOptimalPath(right_point_x, y, x_finish, y_finish, opt_path, arr, rows, columns, shortest_path);
   }
    
}

void cleanMemory(int** arr, int rows)
{
    for (int row = 0; row < rows; ++row )
        delete[] arr[row];
    delete arr;
}

void eval_x_path(std::vector<int>& path, int** shortest_path, int x_begin, int y_begin, int x, int y, int rows)
{
    int i;
    while (x != x_begin || y != y_begin)
    {
        path.push_back(x);
        i = y*rows+x;
        x = shortest_path[i][1];
        y = shortest_path[i][0];

    }
    path.push_back(x);

    std::reverse(path.begin(), path.end());
}

void findOptimalPath(int** arr, std::vector<int>& path, int x_i, int x_f, int rows, int cols)
{
    int y_begin = 0, x_begin = x_i, y_finish = rows - 1, x_finish = x_f;
    
    int** opt_path = new int*[rows];

    for (int row = 0; row < rows; row++)
        opt_path[row] = new int[cols];

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            opt_path[i][j] = 1000000;
        }
    }
    opt_path[y_begin][x_begin] = 0;

    int** shortest_path = new int*[rows*cols];

    for (int i = 0; i < rows*cols; i++)
        shortest_path[i] = new int[2];
    shortest_path[y_begin*rows + x_begin][0] = 0;
    shortest_path[y_begin*rows + x_begin][1] = 0;
    

    evalOptimalPath(x_begin, y_begin, x_finish, y_finish, opt_path, arr, rows, cols, shortest_path);
    
    eval_x_path(path, shortest_path, x_begin, y_begin, x_finish, y_finish, rows);

    cleanMemory(opt_path, rows);
    cleanMemory(shortest_path, rows*cols);
}