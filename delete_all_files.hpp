#ifndef DELETE_ALL_FILES_HPP
#define DELETE_ALL_FILES_HPP

#include <iostream>
#include <filesystem>

using namespace std;

void delete_all_files_func(){
    filesystem::path current_dir = filesystem::current_path();
    string exclude_file = "mygit";
    string exclude_dir = ".mygit";
    try {
        for (const auto& entry : filesystem::directory_iterator(current_dir)) {
            const auto& path = entry.path();

            if (path.filename() == exclude_file || path.filename() == exclude_dir) {
                continue;
            }

            if (filesystem::is_directory(path)) {
                filesystem::remove_all(path);
            } else if (filesystem::is_regular_file(path)) {
                filesystem::remove(path);
            }
        }
    } catch (const filesystem::filesystem_error& e) {
        cout << "Filesystem error: " << e.what() << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

#endif