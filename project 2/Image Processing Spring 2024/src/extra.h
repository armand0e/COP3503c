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
};

struct Pixel {
        unsigned char b;
        unsigned char g;
        unsigned char r;
};

struct Image{
    string path;
    Header header;
    vector<vector<Pixel>> pixelData;
    
    void readImageData();
    void writeImageData(string output);
    void multiply();
    void screen();
    void subtract();
    void addition();
    void overlay();
    Image(string file_path);
};