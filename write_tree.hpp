#ifndef WRITE_TREE_HPP
#define WRITE_TREE_HPP

#include <iostream>
#include <filesystem>

#include "repo_existence.hpp"
#include "random_number_generator.hpp"
#include "hash_object.hpp"
#include "directory_contents.hpp"
#include "add_to_index.hpp"

using namespace std;

string write_tree_func(filesystem::path current_path, bool add_to_index, vector<filesystem::path> files_list){
    
    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return "";
    }

    int current_path_length = (int)current_path.string().size() +1;

    string root_tree_object_temp_path = ".mygit/temp/" + to_string(random_num_func(1,1000000));
    if(!file_creator(root_tree_object_temp_path)){
        return "";
    }

    vector<filesystem::path> directory_contents;
    if(files_list.size()!=0){
        directory_contents = files_list;
    }else{
        directory_contents = directory_contents_func(current_path);
    }
    

    for(const auto& entry : directory_contents){
        string path = entry.string();
        string full_path = path;
        int path_length = (int)path.size();
        path = path.substr(current_path_length, path_length - current_path_length);
        
        if(path == ".mygit" || path == "mygit"){
            continue;
        }

        if(filesystem::is_directory(entry)){
            string tree_object_hash = write_tree_func(entry, add_to_index, {});
            if(tree_object_hash==""){
                return "";
            }
            string tree_object_directory_entry = "040000 tree " + tree_object_hash + " " + path + "\n";

            ofstream fileStream(root_tree_object_temp_path, ios::app);
            if (!fileStream.is_open()) {
                cout << "Failed to open file: " << root_tree_object_temp_path << "\n";
                return "";
            }
            fileStream << tree_object_directory_entry;

        }else{
            string exe = "./mygit";
            string command = "hash-object";
            string flag = "-w";
            char * array_input[] = {&exe[0], &command[0], &flag[0], &full_path[0]};
            string file_hash = hash_object_func(4, array_input,"tree");
            if(file_hash == ""){
                return "";
            }
            
            if(add_to_index){
                add_to_index_func(entry, file_hash);
            }
            
            
            string mode;
            if(filesystem::is_regular_file(entry)){
                mode = "100644"; //regular file              
            }else if(filesystem::is_symlink(entry)){
                mode = "120000"; //symbolic link
            }

            string blob_object_file_entry = mode + " blob " + file_hash + " " + path + "\n";

            ofstream fileStream(root_tree_object_temp_path, ios::app);
            if (!fileStream.is_open()) {
                cout << "Failed to open file: " << root_tree_object_temp_path << "\n";
                return "";
            }
            fileStream << blob_object_file_entry;
        }
    }
    string exe = "./mygit";
    string command = "hash-object";
    string flag = "-w";

    char * array_input[] = {&exe[0], &command[0], &flag[0], &root_tree_object_temp_path[0]};
    string root_tree_hash = hash_object_func(4, array_input,"tree");
    if(root_tree_hash == ""){
        return "";
    }

    remove(root_tree_object_temp_path.c_str());

    return root_tree_hash;
}

#endif