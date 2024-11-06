#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <filesystem>
#include <vector>

#include "cat_file.hpp"
#include "repo_existence.hpp"

using namespace std;

void log_func(){

    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return;
    }

    vector<string> commit_hashes;

    ifstream file(".mygit/ref/heads");
    if(!file){
        cout<< "Error opening file: .mygit/ref/heads\n";
        return;
    }
    string line;
    while(getline(file,line)){
        commit_hashes.push_back(line);
    }
    file.close();

    while(commit_hashes.size()!=0){
        string hash = commit_hashes.back();
        commit_hashes.pop_back();
        string exe = "./mygit";
        string command = "cat-file";
        string flag = "-p";

        char* array_input[] = {&exe[0], &command[0], &flag[0], &hash[0]};
        string commit_object_content = cat_file_func(4, array_input, true);

        cout<<"commit "<<hash<<"\n";
        cout<<commit_object_content;
        cout<<"********************\n";
    }
}

#endif