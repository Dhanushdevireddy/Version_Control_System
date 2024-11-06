#ifndef COMMIT_HPP
#define COMMIT_HPP

#include <iostream>
#include <chrono>
#include <ctime>
#include <filesystem>

#include "repo_existence.hpp"

using namespace std;

string commit_func(int num_of_args, char* args[]){
    if(!repo_exists()){
        cout<<"Please create Repository.\n";
        return "";
    }
    
    string index_path = ".mygit/index";
    ifstream inputFile(index_path);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << index_path << '\n';
        return "";
    }

    string lastLine;
    string line;

    while (getline(inputFile, line)) {
        lastLine = line;
    }

    inputFile.close();
    string cwd_hash;

    if (lastLine.rfind("cwd_hash ", 0) == 0) {
        size_t spacePos = lastLine.find(' ');
        if (spacePos != string::npos && spacePos + 1 < lastLine.length()) {
            cwd_hash = lastLine.substr(spacePos + 1);
        }
    }

    string head_path = ".mygit/HEAD";
    if (!filesystem::exists(head_path)) {
        cout << "Error: File does not exist: " << head_path << '\n';
        return "";
    }
    
    ifstream inputFile2(head_path);
    if (!inputFile2.is_open()) {
        cout << "Error opening file: " << head_path << '\n';
        return "";
    }

    string parent_commit_hash;
    getline(inputFile2, parent_commit_hash);
    inputFile2.close();

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    string time_str = ctime(&now_time);

    string commit_message;
    if(num_of_args>3 && strcmp(args[2],"-m")==0){
        for(int i = 3; i<num_of_args;i++){
            commit_message += args[i];
        }
    }else{
        commit_message = "Committed!!!!";
    }

    string commit_object_content = "tree " + cwd_hash + "\nparent" + " " + parent_commit_hash + "\ncommitter DhanushDevireddy\n" + "timestamp "+ time_str + commit_message + "\n";

    string commit_object_temp_path = ".mygit/temp/" + to_string(random_num_func(1,1000000));
    if(!file_creator(commit_object_temp_path)){
        return "";
    }

    ofstream fileStream(commit_object_temp_path, ios::app);
    if (!fileStream.is_open()) {
        cout << "Failed to open file: " << commit_object_temp_path << "\n";
        return "";
    }
    fileStream << commit_object_content;
    fileStream.close();
    
    string exe = "./mygit";
    string command = "hash-object";
    string flag = "-w";

    char * array_input[] = {&exe[0], &command[0], &flag[0], &commit_object_temp_path[0]};
    string commit_hash = hash_object_func(4, array_input,"commit");
    if(commit_hash == ""){
        return "";
    }

    remove(commit_object_temp_path.c_str());

    remove(".mygit/HEAD");
    if(!file_creator(head_path)){
        return "";
    }

    ofstream fileStream2(head_path, ios::app);
    if (!fileStream2.is_open()) {
        cout << "Failed to open file: " << head_path << "\n";
        return "";
    }
    fileStream2 << commit_hash;
    fileStream2.close();

    string ref_heads = ".mygit/ref/heads";
    ofstream refHeadStream(ref_heads, ios::app);
    if (!refHeadStream.is_open()) {
        cout << "Failed to open file: " << ref_heads << "\n";
        return "";
    }
    refHeadStream << commit_hash <<"\n";
    refHeadStream.close();

    return commit_hash;
}

#endif