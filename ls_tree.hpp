#ifndef LS_TREE_HPP
#define LS_TREE_HPP

#include <iostream>
#include <cstring>

#include "repo_existence.hpp"
#include "cat_file.hpp"

using namespace std;

string ls_tree_func(int num_of_args, char * args[]){
    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return "";
    }

    if(num_of_args<3){
        cout<<"Please give more arguments.\n";
        return "";
    }

    string exe = "./mygit";
    string command = "cat-file";
    string flag = "-p";

    string object_content;
    if(num_of_args==3){
        char* array_input[] = {&exe[0], &command[0], &flag[0], args[2]};
        object_content = cat_file_func(4, array_input, true);
        return object_content;
    }

    if(num_of_args==4 && strcmp(args[2],"--name-only")==0){
        char* array_input[] = {&exe[0], &command[0], &flag[0], args[3]};
        object_content = cat_file_func(4, array_input, true);

        string temp;
        string output;
        for(int i =0; i<(int)object_content.size();i++){
            if(object_content[i]==' '){
                temp = "";
            }else{
                temp += object_content[i];
                if(object_content[i]=='\n'){
                    output += temp;
                    temp = "";
                }
            }
        }
        return output;
    }
    return "";
}

#endif