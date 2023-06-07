#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "tree.h"

int main(int argc, char **argv){
    if (argc < 3) {
        std::cerr << "Wrong number of input arguments" << std::endl;
        return -1;
    }

    if (std::stoi(argv[2]) != argc - 3) {
        std::cerr << "Number of arguments for deleting is incorrect" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        return -1;
    }
    std::string line;

    int value;
    int id = 0;

    Node tree, *root = nullptr;

    std::vector<int> delete_points;
    for (int i = 0; i < std::stoi(argv[2]); i++)
        delete_points.push_back(std::stoi(argv[3+i]));

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (iss >> value) 
        {
            if (std::find(delete_points.begin(), delete_points.end(), value) == delete_points.end()){
                KeyValue elem(id, value);
                root = tree.addNode(root, elem);
            }
            else                
                std::cerr << "delete elem" << std::endl;
            id++;
        }
    }
    tree.sort_tree(root);
    tree.deleteTree(root);
    return 0;
}