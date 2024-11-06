#ifndef DECOMPRESS_HPP
#define DECOMPRESS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>

using namespace std;

string decompress_func(bool type, bool size, string file_path, bool ls_tree_flag, string output_file_path){
    const int CHUNK_SIZE = 4096;
    ifstream file(file_path, ios::binary);
    if (!file) {
        cout << "Error opening file: " << file_path << "\n";
        return "";
    }

    z_stream strm{};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    if (inflateInit(&strm) != Z_OK) {
        cout << "Failed to initialize zlib for decompression.\n";
        return "";
    }

    vector<char> in_buffer(CHUNK_SIZE);
    vector<char> out_buffer(CHUNK_SIZE);
    vector<char> decompressed_data;

    string object_content;
    int ret;
    do {
        file.read(in_buffer.data(), in_buffer.size());
        strm.avail_in = file.gcount();
        if (strm.avail_in == 0) break;
        strm.next_in = reinterpret_cast<Bytef*>(in_buffer.data());
        int iteration = 0;

        do {
            strm.avail_out = out_buffer.size();
            strm.next_out = reinterpret_cast<Bytef*>(out_buffer.data());

            ret = inflate(&strm, Z_NO_FLUSH);

            if (ret == Z_STREAM_ERROR) {
                cout << "Stream error during decompression.\n";
                inflateEnd(&strm);
                return "";
            } else if (ret == Z_DATA_ERROR) {
                cout << "Data error: incorrect file format.\n";
                inflateEnd(&strm);
                return "";
            } else if (ret == Z_MEM_ERROR) {
                cout << "Memory error during decompression.\n";
                inflateEnd(&strm);
                return "";
            }

            int have = CHUNK_SIZE - strm.avail_out;
            decompressed_data.insert(decompressed_data.end(), out_buffer.begin(), out_buffer.begin() + have);

            if(type || size){
                if(type){
                    for(int i = 0;i<(int)decompressed_data.size();i++){
                        if(decompressed_data[i] == ' '){
                            cout<<"\n";
                            return "";
                        }
                        cout<<decompressed_data[i];
                    }
                    cout<<"\n";
                    return "";
                }
                int i = 0;
                for(;i<(int)decompressed_data.size();i++){
                    if(decompressed_data[i] == ' '){
                        i++;
                        break;
                    }
                }
                for(;i<(int)decompressed_data.size();i++){
                    if(decompressed_data[i] == '\0'){
                        cout<<"\n";
                        return "";
                    }
                    cout<<decompressed_data[i];
                }
                cout<<"\n";

                return "";
            }
            int i = 0;
            if(iteration==0){
                for(;i<(int)decompressed_data.size();i++){
                    if(decompressed_data[i] == '\0'){
                        i++;
                        break;
                    }
                }
            }
            for (; i < (int)decompressed_data.size();i++) {
                if(ls_tree_flag){
                    object_content += decompressed_data[i];
                }else{
                    if(output_file_path==""){
                        cout << decompressed_data[i];
                    }else{
                        ofstream outFile(output_file_path, ios::app);
                        if (!outFile) {
                            cout << "Error opening file: " << output_file_path << "\n";
                            return "";
                        }
                        outFile << decompressed_data[i];
                        outFile.flush();
                        outFile.close();
                    }
                }
            }
            decompressed_data.clear();
            iteration++;

        } while (strm.avail_out == 0);

    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    if(!ls_tree_flag && output_file_path.size()==0){
        cout << "\n";
    }

    return object_content;
    
}

#endif