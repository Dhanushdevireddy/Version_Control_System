#ifndef CAT_FILE_HPP
#define CAT_FILE_HPP

#include <iostream>
#include <cstring>

#include "repo_existence.hpp"
#include "decompress.hpp"

using namespace std;

string cat_file_func(int num_of_args, char * args[], bool ls_tree_flag){
    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return "";
    }

    if(num_of_args<4){
        cout<<"3 arguments are required.\n";
        return "";
    }

    string hash = args[3];

    if(hash.size()!=40){
        cout<<"Please give proper hash.\n";
        return "";
    }

    string file_path = ".mygit/objects/" + hash.substr(0,2) + "/" + hash.substr(2, 38);

    if(strcmp(args[2], "-t")==0){
        string object_content = decompress_func(true, false, file_path, ls_tree_flag,"");
        return object_content;
    }

    if(strcmp(args[2], "-s")==0){
        string object_content = decompress_func(false, true, file_path, ls_tree_flag, "");
        return object_content;
    }

    if(strcmp(args[2], "-p")==0){
        string object_content = decompress_func(false, false, file_path, ls_tree_flag, "");
        return object_content;
    }

    return "";

}

#endif