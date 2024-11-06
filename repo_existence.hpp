#ifndef REPO_EXISTENCE_HPP
#define REPO_EXISTENCE_HPP

#include <iostream>
#include <filesystem>

using namespace std;

bool repo_exists(){
    return filesystem::exists(".mygit") && filesystem::is_directory(".mygit");
}

#endif