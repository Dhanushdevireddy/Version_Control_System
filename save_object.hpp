#ifndef SAVE_OBJECT_HPP
#define SAVE_OBJECT_HPP

#include <iostream>

#include "compress.hpp"
#include "create_directory.hpp"
#include "create_file.hpp"

using namespace std;

void save_object_func(string sha1_hash, string file_path, string header){
    string directory_path = ".mygit/objects/" + sha1_hash.substr(0,2);

    if(filesystem::exists(directory_path)){
        return;
    }

    if(!directory_creator(directory_path)){
        return;
    }

    string file_name = sha1_hash.substr(2, 38);
    if(!file_creator(directory_path + "/" +file_name)){
        return;
    }

    compress_func(file_path, directory_path + "/" + file_name, header);
}

#endif