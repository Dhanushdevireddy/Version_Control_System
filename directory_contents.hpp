#ifndef DIRECTORY_CONTENTS_HPP
#define DIRECTORY_CONTENTS_HPP

#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;

vector<filesystem::path> directory_contents_func(filesystem::path directory){
    vector<filesystem::path> directory_contents;
    for (const auto& entry : filesystem::directory_iterator(directory)) {
        directory_contents.push_back(entry.path());
    }
    return directory_contents;
}
#endif