#ifndef ADD_HPP
#define ADD_HPP

#include <iostream>
#include <cstring>
#include <filesystem>

#include "repo_existence.hpp"
#include "write_tree.hpp"
#include "create_file.hpp"
#include "add_to_index.hpp"

using namespace std;

void add_func(int num_of_args, char* args[]){
    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return;
    }

    if(num_of_args<3){
        cout<<"Please give more arguments.\n";
        return;
    }

    string index_path = ".mygit/index";
    if(!filesystem::exists(index_path)){
        if(!file_creator(index_path)){
            return;
        }
    }
    string tree_hash;
    if(num_of_args==3 && strcmp(args[2], ".")==0){
        remove(&index_path[0]);
        if(!file_creator(index_path)){
            return;
        }
        filesystem::path current_path = filesystem::current_path();
        tree_hash = write_tree_func(current_path, true, {});
    }else{
        filesystem::path current_path = filesystem::current_path();
        string current_path_string = current_path.string();
        vector<filesystem::path> files;

        for(int i =2;i<num_of_args;i++){
            filesystem::path filePath(current_path_string + "/" + args[i]);
            files.push_back(filePath);
        }
        tree_hash = write_tree_func(current_path,true , files);
    }

    add_to_index_func("cwd_hash", tree_hash);
}

#endif