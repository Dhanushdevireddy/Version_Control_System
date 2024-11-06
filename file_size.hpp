#ifndef FILE_SIZE_HPP
#define FILE_SIZE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

int file_size_func(string file_path){
    ifstream file(file_path, ios::binary);
    if (!file) {
        cout<<"Error opening file: "<<file_path<<"\n";
        return -1;
    }
    file.seekg(0, ios::end);
    long fileSize = file.tellg();

    if (file.fail()) {
        cout << "Error determining the size of the file: " << file_path << "\n";
        return -1;
    }
    
    file.close();
    
    return fileSize;
}

#endif