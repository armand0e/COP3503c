#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    Header& operator=(Header& d) {
        
    }
};

struct pixel {
        unsigned char b;
        unsigned char g;
        unsigned char r;
};

struct Image{
    string path;
    Header header;
    vector<vector<pixel>> imageData;
    
    void readHeader();
    void printHeader();
    void readImageData();
    void writeImageToFile(string output);
    Image(string file_path);
};