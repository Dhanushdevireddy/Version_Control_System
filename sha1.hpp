#ifndef SHA1_HPP
#define SHA1_HPP

#include <iostream>
#include <fstream>
#include <openssl/evp.h>
#include <string>
#include <vector>

using namespace std;

string sha1_hash_func(string file_path, string header){
    
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        cout<<"Failed to create hash context.\n";
        return "";
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha1(), nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
        cout<<"Failed to initialize SHA-1.\n";
        return "";
    }

    if (EVP_DigestUpdate(ctx, header.c_str(), header.size()) != 1) {
        EVP_MD_CTX_free(ctx);
        cout << "Failed to update SHA-1 with header.\n";
        return "";
    }

    ifstream file(file_path, ios::binary);
    if (!file) {
        EVP_MD_CTX_free(ctx);
        cout << "Error opening file: " << file_path << "\n";
        return "";
    }

    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    while (file.read(buffer, buffer_size) || file.gcount() > 0) {
        if (EVP_DigestUpdate(ctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(ctx);
            cout << "Failed to update SHA-1 with file content.\n";
            return "";
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length = 0;
    if (EVP_DigestFinal_ex(ctx, hash, &hash_length) != 1) {
        EVP_MD_CTX_free(ctx);
        cout << "Failed to finalize SHA-1.\n";
        return "";
    }

    EVP_MD_CTX_free(ctx);

    string hash_string;
    for (unsigned int i = 0; i < hash_length; ++i) {
        hash_string += (hash[i] / 16 < 10 ? '0' + (hash[i] / 16) : 'a' + (hash[i] / 16 - 10));
        hash_string += (hash[i] % 16 < 10 ? '0' + (hash[i] % 16) : 'a' + (hash[i] % 16 - 10));
    }

    return hash_string;
}

#endif