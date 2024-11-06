#ifndef HASH_OBJECT_HPP
#define HASH_OBJECT_HPP

#include <iostream>

#include "repo_existence.hpp"
#include "sha1.hpp"
#include "save_object.hpp"
#include "file_size.hpp"

using namespace std;

string hash_object_func(int num_of_args, char * args[], string object_type){

    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return "";
    }

    if(num_of_args<3){
        cout<<"Please give more arguments.\n";
        return "";
    }

    if(num_of_args>4){
        cout<<"Maximum 4 arguments are allowed.\n";
        return "";
    }

    string file_name = (num_of_args==3)?args[2]:args[3];
    int file_size = file_size_func(file_name);

    string header = object_type + " " + to_string(file_size) + "\0";

    string sha1_hash = sha1_hash_func(file_name, header);
    if(sha1_hash==""){
        return "";
    }

    if(num_of_args == 3){
        return sha1_hash;
    }

    if(num_of_args==4 && strcmp(args[2],"-w")==0){
        save_object_func(sha1_hash, file_name, header);
    }else{
        cout<<"Give proper arguments.\n";
        return sha1_hash;
    }
    return sha1_hash;

}

#endif