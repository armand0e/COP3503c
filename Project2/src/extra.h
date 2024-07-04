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
    // path to read data from
    string path;
    // header obj to store header data
    Header header;
    // total number of pixels
    int pixelCount;
    // 2-D list of all pixels, each pixel is it's own vector -> [[R, G, B], [R, G, B], ...]
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
    void addToChannel(int num, int channel);
    void multiplyToChannel(int num, int channel);
    void combineImages(Image red, Image green, Image blue);
    void flipVertically();
    Image(string file_path);
};
