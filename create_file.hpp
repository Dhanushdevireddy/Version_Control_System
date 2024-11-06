#ifndef CREATE_FILE_HPP
#define CREATE_FILE_HPP

#include <iostream>
#include <fstream>

using namespace std;

bool file_creator(string file_path){
    ofstream file(file_path);
    if(!file){
        cout<<"Error creating file: "<<file_path<<"\n";
        return false;
    }
    return true;
}

#endif