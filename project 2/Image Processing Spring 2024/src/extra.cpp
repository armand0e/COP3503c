#include "extra.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void Image::readHeader() {
    fstream file(path, ios_base::in | ios_base::binary);
    if (file.is_open()) {
        file.read(&header.idLength, 1);
        file.read(&header.colorMapType, 1);
        file.read(&header.dataTypeCode, 1);
        file.read(reinterpret_cast<char*>(&header.colorMapOrigin), 2);
        file.read(reinterpret_cast<char*>(&header.colorMapLength), 2);
        file.read(&header.colorMapDepth, 1);
        file.read(reinterpret_cast<char*>(&header.xOrigin), 2);
        file.read(reinterpret_cast<char*>(&header.yOrigin), 2);
        file.read(reinterpret_cast<char*>(&header.width), 2);
        file.read(reinterpret_cast<char*>(&header.height), 2);
        file.read(&header.bitsPerPixel, 1);
        file.read(&header.imageDescriptor, 1);
    }
}

void Image::printHeader() {
    cout << (int)header.idLength << endl;
    cout << (int)header.colorMapType << endl;
    cout << (int)header.dataTypeCode << endl;
    cout << (int)header.colorMapOrigin << endl;
    cout << (int)header.colorMapLength << endl;
    cout << (int)header.colorMapDepth << endl;
    cout << header.xOrigin << endl;
    cout << header.yOrigin << endl;
    cout << header.width << endl;
    cout << header.height << endl;
    cout << (int)header.bitsPerPixel << endl;
    cout << (int)header.imageDescriptor << endl;
}

void Image::readImageData() {
    cout << "readimagedata" << endl;
}

void Image::writeImageToFile(string output) {
    cout << "readimagedata" << endl;
}

Image::Image(string file_path) {
    path = file_path;
    readHeader();
    //readImageData();
}