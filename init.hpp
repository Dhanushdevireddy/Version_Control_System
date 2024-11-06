#ifndef INIT_HPP
#define INIT_HPP

#include <iostream>
#include <filesystem>
#include <fstream>

#include "repo_existence.hpp"
#include "create_directory.hpp"
#include "create_file.hpp"

using namespace std;

void init_func(){
    if(repo_exists()){
        cout<<"Repository already exists.\n";
        return;
    }

    string directory_path = ".mygit";
    if(!directory_creator(directory_path)){
        return;
    }

    string file_name = "HEAD";
    if(!file_creator(directory_path + "/" + file_name)){
        return;
    }

    string directory_name = "objects";
    if(!directory_creator(directory_path + "/" + directory_name)){
        return;
    }

    directory_name = "temp";
    if(!directory_creator(directory_path + "/" + directory_name)){
        return;
    }

    directory_name = "ref";
    if(!directory_creator(directory_path + "/" + directory_name)){
        return;
    }

    file_name = "heads";
    if(!file_creator(directory_path + "/ref" + "/" + file_name)){
        return;
    }

    cout<<"Repository created successfully.\n";

    return;
}

#endif