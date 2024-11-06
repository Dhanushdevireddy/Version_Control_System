#include <iostream>
#include <cstring>
#include <filesystem>

#include "init.hpp"
#include "hash_object.hpp"
#include "cat_file.hpp"
#include "write_tree.hpp"
#include "ls_tree.hpp"
#include "add.hpp"
#include "commit.hpp"
#include "log.hpp"
#include "checkout.hpp"
#include "delete_all_files.hpp"

using namespace std;

int main(int argc, char * argv[]){

    if(argc<2){
        cout<<"Please give more arguments.\n";
        exit(0);
    }

    if(strcmp(argv[1], "init")==0){
        init_func();
        exit(0);
    }

    if(strcmp(argv[1], "hash-object")==0){
        string hash = hash_object_func(argc,argv, "blob");
        if(hash!=""){
            cout<<hash<<"\n";
        }
        exit(0);
    }

    if(strcmp(argv[1], "cat-file")==0){
        cat_file_func(argc, argv, false);
        exit(0);
    }

    if(strcmp(argv[1], "write-tree")==0){
        filesystem::path current_path = filesystem::current_path();
        string tree_hash = write_tree_func(current_path, false,{});
        if(tree_hash!=""){
            cout<<tree_hash<<"\n";
        }
        exit(0);
    }

    if(strcmp(argv[1], "ls-tree")==0){
        string object_content = ls_tree_func(argc,argv);
        if(object_content != ""){
            cout<<object_content;
        }
        exit(0);
    }

    if(strcmp(argv[1], "add")==0){
        add_func(argc, argv);
        exit(0);
    }

    if(strcmp(argv[1], "commit")==0){
        string commit_hash = commit_func(argc,argv);
        if(commit_hash!=""){
            cout<<commit_hash<<"\n";
        }
        exit(0);
    }

    if(strcmp(argv[1], "log")==0){
        log_func();
        exit(0);
    }

    if(strcmp(argv[1], "checkout")==0){
        if(argc<3){
            cout<<"Please give more arguments.\n";
            exit(0);
        }
        delete_all_files_func();
        checkout_func(argv[2]);
        exit(0);
    }

    cout<<"Give proper command.\n";

    return 0;
}