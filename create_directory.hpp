#ifndef CREATE_DIRECTORY_HPP
#define CREATE_DIRECTORY_HPP

#include <iostream>
#include <filesystem>

using namespace std;

bool directory_creator(string directory_path){
    if(!filesystem::create_directory(directory_path)){
        cout<<"Error creating directory: "<<directory_path<<"\n";
        return false;
    }
    return true;
}

#endif