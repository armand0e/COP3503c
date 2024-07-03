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

struct Image {
    string path;
    Header header;
    int pixelCount;
    vector<vector<unsigned char>> pixels;
    
    void readImageData();
    void writeImageData(string output);
    void multiply(Image otherImage);
    void screen(Image otherImage);
    void subtract(Image otherImage);
    void addition(Image otherImage);
    void overlay(Image otherImage);
    void extractRed();
    void extractGreen();
    void extractBlue();
    void combineImages(Image red, Image green, Image blue);
    void flipVertically();
    Image(string file_path);
};
