#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "opt_path.h"

int main(int argc, char* argv[]) {
    
    if (argc != 7) {
        std::cerr << "Wrong input arguments" << std::endl;
        return -1;
    }
    int rows = stoi(argv[2]), cols = stoi(argv[3]); // определение строк и столбцов как у матрицы в математике
    int x_i = stoi(argv[4]), x_f = stoi(argv[5]);
    char *input_file = argv[1], *output_file = argv[6];

    // читаем png изображение
    std::vector<unsigned char> image; // vector to store value of pixels with all 4 channels RGBA
    decodeFromPng(image, input_file, rows, cols); // read png file

    
    // способ 3 стр. 115 создания двумерного массива
    // выделяем память
    
    int** arr = new int*[rows];
    for (int row = 0; row < rows; ++row )
        arr[row] = new int[cols];

    // инициализируем выделенный массив arr синим каналом нашего изображения
    getBlueChannel(image, arr, rows, cols);  

    // можно опционально выводить массив в консоль для отладки 
    printArray(arr, rows, cols);  
    
    //функцию ниже вам нужно реализовать
    //-----------------------------------------------------------------------------
    std::vector<int> path;
    // вектор к которому нужно делать push_back для добавления точек пути 
    std::cout << "ready to work!" << std::endl;

    findOptimalPath(arr, path, x_i, x_f, rows, cols);
   //------------------------------------------------------------------------------


    // далее можно отрисовать path используя фукцию ниже
    drawPath(path, image, rows, cols, output_file);

    // очищаем память
    cleanMemory(arr, rows);
    return 0;
}

