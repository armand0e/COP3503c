#include "extra.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void Image::readImageData() {
    fstream file(path, ios_base::in | ios_base::binary);
    if (file.is_open()) {
        // read header
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
        // read pixels
        for (int row = 0; row < header.height; row++) {
            vector<Pixel> newRow;
            for (int col = 0; col < header.width; col++) {
                Pixel newPixel;
                file.read(reinterpret_cast<char*>(&newPixel.b), 1);
                file.read(reinterpret_cast<char*>(&newPixel.g), 1);
                file.read(reinterpret_cast<char*>(&newPixel.r), 1);
                newRow.push_back(newPixel);
            }
            pixelData.push_back(newRow);
        }
    }
}

void Image::writeImageData(string output) {
    fstream file(output, ios_base::out | ios_base::binary);
    /* cout << (int)header.idLength << endl;
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
    for (int row = 0; row < header.height; row++) {
        for (int col = 0; col < header.width; col++) {
            Pixel currentPixel = pixelData[row][col];
            cout << (int)currentPixel.b << " ";
            cout << (int)currentPixel.g << " ";
            cout << (int)currentPixel.r << " ";
        }
        cout << endl;
    } */
    // write header
    file.write(&header.idLength, 1);
    file.write(&header.colorMapType, 1);
    file.write(&header.dataTypeCode, 1);
    file.write(reinterpret_cast<char*>(&header.colorMapOrigin), 2);
    file.write(reinterpret_cast<char*>(&header.colorMapLength), 2);
    file.write(&header.colorMapDepth, 1);
    file.write(reinterpret_cast<char*>(&header.xOrigin), 2);
    file.write(reinterpret_cast<char*>(&header.yOrigin), 2);
    file.write(reinterpret_cast<char*>(&header.width), 2);
    file.write(reinterpret_cast<char*>(&header.height), 2);
    file.write(&header.bitsPerPixel, 1);
    file.write(&header.imageDescriptor, 1);
    // write pixels
    for (int row = 0; row < header.height; row++) {
        for (int col = 0; col < header.width; col++) {
            Pixel currentPixel = pixelData[row][col];
            file.write(reinterpret_cast<char*>(&currentPixel.b), 1);
            file.write(reinterpret_cast<char*>(&currentPixel.g), 1);
            file.write(reinterpret_cast<char*>(&currentPixel.r), 1);
        }
    }
}






Image::Image(string file_path) {
    path = file_path;
    readImageData();
}