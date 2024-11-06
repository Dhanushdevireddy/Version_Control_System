#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <iostream>
#include <fstream>
#include <zlib.h>
#include <string>
#include <vector>

using namespace std;

void compress_func(string file_path, string destination_path, string header){
    
    ifstream source_file(file_path, ios::binary);
    if (!source_file) {
        cout << "Failed to open file: " << file_path << "\n";
        return;
    }

    ofstream dest_file(destination_path, ios::binary);
    if (!dest_file) {
        cout << "Failed to open file: " << destination_path << "\n";
        return;
    }

    z_stream deflate_stream;
    deflate_stream.zalloc = Z_NULL;
    deflate_stream.zfree = Z_NULL;
    deflate_stream.opaque = Z_NULL;

    if (deflateInit(&deflate_stream, Z_BEST_COMPRESSION) != Z_OK) {
        cout << "Failed to initialize compression.\n";
        return;
    }

    vector<char> header_vector;
    for(int i =0;i<(int)header.size();i++){
        header_vector.push_back(header[i]);
    }
    header_vector.push_back('\0');

    deflate_stream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(header_vector.data()));
    deflate_stream.avail_in = header_vector.size();

    vector<char> out_buffer(4096);

    do {
        deflate_stream.next_out = reinterpret_cast<Bytef*>(out_buffer.data());
        deflate_stream.avail_out = out_buffer.size();

        if (deflate(&deflate_stream, Z_NO_FLUSH) == Z_STREAM_ERROR) {
            cout << "Compression error while adding header.\n";
            deflateEnd(&deflate_stream);
            return;
        }

        dest_file.write(out_buffer.data(), out_buffer.size() - deflate_stream.avail_out);
    } while (deflate_stream.avail_in > 0);

    vector<char> in_buffer(4096);
    while (source_file.read(in_buffer.data(), in_buffer.size()) || source_file.gcount() > 0) {
        deflate_stream.next_in = reinterpret_cast<Bytef*>(in_buffer.data());
        deflate_stream.avail_in = source_file.gcount();

        do {
            deflate_stream.next_out = reinterpret_cast<Bytef*>(out_buffer.data());
            deflate_stream.avail_out = out_buffer.size();

            if (deflate(&deflate_stream, Z_NO_FLUSH) == Z_STREAM_ERROR) {
                cout << "Compression error while processing file.\n";
                deflateEnd(&deflate_stream);
                return;
            }

            dest_file.write(out_buffer.data(), out_buffer.size() - deflate_stream.avail_out);
        } while (deflate_stream.avail_in > 0);
    }

    do {
        deflate_stream.next_out = reinterpret_cast<Bytef*>(out_buffer.data());
        deflate_stream.avail_out = out_buffer.size();

        if (deflate(&deflate_stream, Z_FINISH) == Z_STREAM_ERROR) {
            cout << "Error finishing compression.\n";
            deflateEnd(&deflate_stream);
            return;
        }

        dest_file.write(out_buffer.data(), out_buffer.size() - deflate_stream.avail_out);
    } while (deflate_stream.avail_out == 0);

    deflateEnd(&deflate_stream);
    source_file.close();
    dest_file.close();

    return;

}

#endif