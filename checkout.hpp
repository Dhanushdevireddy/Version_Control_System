#ifndef CHECKOUT_HPP
#define CHECKOUT_HPP

#include <iostream>
#include <filesystem>
#include <string>

#include "repo_existence.hpp"
#include "cat_file.hpp"
#include "create_file.hpp"
#include "decompress.hpp"
#include "create_directory.hpp"

using namespace std;

vector<vector<string>> string_to_vector(string input){
    vector<vector<string>> result;
    stringstream ss(input);
    string line;

    while (getline(ss, line)) {
        vector<string> words;
        stringstream lineStream(line);
        string word;

        while (lineStream >> word) {
            words.push_back(word);
        }
        if (!words.empty()) {
            result.push_back(words);
        }
    }

    return result;
}

void tree_object_traversal(string current_dir, string hash){
    string exe = "./mygit";
    string command = "cat-file";
    string flag = "-p";

    char* array_input[] = {&exe[0], &command[0], &flag[0], &hash[0]};
    string tree_object_content = cat_file_func(4, array_input, true);

    vector<vector<string>> tree_object = string_to_vector(tree_object_content);

    for(int i =0; i<(int)tree_object.size();i++){
        if(tree_object[i][1] == "tree"){
            if(!directory_creator(current_dir + "/" + tree_object[i][3])){
                return;
            }
            tree_object_traversal(current_dir + "/" + tree_object[i][3], tree_object[i][2]);
        }else{
            string file_path = current_dir + "/" + tree_object[i][3];
            if(!file_creator(file_path)){
                return;
            }
            string blob_object_path = ".mygit/objects/" + tree_object[i][2].substr(0,2) + "/" + tree_object[i][2].substr(2,38);
            decompress_func(false, false, blob_object_path, false,file_path);
        }
    }
    
}

void checkout_func(string hash){
    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return;
    }

    string exe = "./mygit";
    string command = "cat-file";
    string flag = "-p";

    char* array_input[] = {&exe[0], &command[0], &flag[0], &hash[0]};
    string commit_object_content = cat_file_func(4, array_input, true);

    string tree_hash;
    bool space_discovered = false;
    for(int i =0;i<(int)commit_object_content.size();i++){
        if(commit_object_content[i]==' '){
            space_discovered = true;
            continue;
        }
        if(commit_object_content[i]=='\n'){
            break;
        }
        if(space_discovered){
            tree_hash+=commit_object_content[i];
        }
    }

    remove(".mygit/HEAD");
    remove(".mygit/index");

    string head_path = ".mygit/HEAD";
    string index_path = ".mygit/index";
    if(!file_creator(head_path)){
        return;
    }
    if(!file_creator(index_path)){
        return;
    }

    ofstream headFile(head_path, ios::app);
    if (!headFile) {
        cout << "Error opening file: " << head_path << "\n";
        return;
    }
    headFile << hash;
    headFile.flush();
    headFile.close();

    ofstream indexFile(index_path, ios::app);
    if (!indexFile) {
        cout << "Error opening file: " << index_path << "\n";
        return;
    }
    indexFile << "cwd_hash " + tree_hash + "\n";
    indexFile.flush();
    indexFile.close();

    string current_dir = filesystem::current_path().string();
    tree_object_traversal(current_dir, tree_hash);
}

#endif