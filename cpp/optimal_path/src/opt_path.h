#include <vector>
using namespace std;

void decodeFromPng(vector<unsigned char>& image, const char* filename, unsigned height, unsigned width);
void getBlueChannel(const vector<unsigned char>& image, int** arr, int rows, int cols);
void printArray(int** arr, int rows, int cols);
void drawPath(const vector<int>& path, vector<unsigned char>& image, int rows, int cols, const char* output_file);
void evalOptimalPath(int x, int y, int x_finish, int y_finish, int** opt_path, int** arr, int rows, int columns, int** shortest_path);
void cleanMemory(int** arr, int rows);
void eval_x_path(vector<int>& path, int** shortest_path, int x_begin, int y_begin, int x, int y, int rows);
void findOptimalPath(int** arr, vector<int>& path, int x_i, int x_f, int rows, int cols);