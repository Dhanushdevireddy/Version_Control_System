#ifndef ADD_TO_INDEX_HPP
#define ADD_TO_INDEX_HPP

#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

void add_to_index_func(filesystem::path file_path, string hash) {
    string file_path_string = file_path.string();
    string index_entry = file_path_string + " " + hash + "\n";
    string index_path = ".mygit/index";

    ifstream inputFile(index_path);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << index_path << '\n';
        return;
    }

    ofstream tempFile(".mygit/temp/tempfile");
    if (!tempFile.is_open()) {
        cout << "Error creating temporary file.\n";
        return;
    }

    bool updated = false;
    bool found = false;
    string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string currentPath, currentHash;

        if (!(iss >> currentPath >> currentHash)) {
            tempFile << line << '\n';
            continue;
        }

        if (currentPath == file_path_string) {
            found = true;
            if (currentHash != hash) {
                tempFile << file_path_string << ' ' << hash << '\n';
                updated = true;
            } else {
                tempFile << line << '\n';
            }
        } else {
            tempFile << line << '\n';
        }
    }

    if (!found) {
        tempFile << index_entry;
        updated = true;
    }

    inputFile.close();
    tempFile.close();

    if (updated) {
        filesystem::remove(index_path);
        filesystem::rename(".mygit/temp/tempfile", index_path);
    } else {
        filesystem::remove(".mygit/temp/tempfile");
    }
}

#endif