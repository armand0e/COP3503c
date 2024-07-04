#include "extra.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// useful funcs
int capped(int pixelValue) {
    if (pixelValue > 255) {
        pixelValue = 255;
    }
    if (pixelValue < 0) {
        pixelValue = 0;
    }
    return pixelValue;
}
float normalize(int pixelValue) {
    return pixelValue / 255.0f;
}
int unnormalize(float normalizedValue) {
    return static_cast<int>(normalizedValue * 255 + 0.5f);
}

////////////////////// Image Struct ////////////////////////

// Constructor
Image::Image(string file_path) {
    // store path
    path = file_path;
    readImageData();
}

void Image::readImageData() {
    // open file from path
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
        // store pixelCount to use for looping later.
        pixelCount = header.height * header.width;
        // resize our vector ahead of time for efficiency
        pixels.resize(pixelCount, vector<unsigned char>(3));
        // read pixels
        for (int i = 0; i < pixelCount; ++i) {
            // for every single pixel... 
            for (int j = 2; j >= 0; j--) {
                // read BGR (stored as RGB)
                file.read(reinterpret_cast<char*>(&pixels[i][j]), 1);
            }
        }
        file.close();
    } 
    else {
        throw runtime_error("Failed to open file(s)");
    }
}

void Image::writeImageData(string output) {
    fstream file(output, ios_base::out | ios_base::binary);
    if (file.is_open()) {
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
        for (int i = 0; i < pixels.size(); ++i) {
            for (int j = 2; j >= 0; j--) {
                // write BGR (stored as RGB)
                file.write(reinterpret_cast<char*>(&pixels[i][j]), 1);
            }
        }
        file.close();
    } 
    else {
        throw runtime_error("Failed to open file(s)");
    }
}

void Image::multiply(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        // for every single pixel...
        for (int j = 0; j < 3; j++) {
            // for every channel, [R, G, B]
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // NP1 * NP2
            int multipliedValue = capped(unnormalize(normalize(p1) * normalize(p2)));
            pixels[i][j] = (unsigned char)multipliedValue;
        }
    }
}

void Image::screen(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // 1 - [(1 - NP1) * (1 - NP2)]
            int screenedValue = capped(unnormalize(1 - ((1 - normalize(p1)) * (1 - normalize(p2)))));
            pixels[i][j] = (unsigned char)screenedValue;
        }
    }
}

void Image::subtract(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // P1 - P2
            int subtractedValue = capped(p1 - p2);
            pixels[i][j] = (unsigned char)subtractedValue;
        }
    }
}

void Image::addition(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // P1 + P2
            int sum = capped(p1 + p2);
            pixels[i][j] = (unsigned char)sum;
        }
    }
}

void Image::overlay(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // NP2 <= 0.5: 2 * NP1 * NP2
            // NP2 > 0.5: 1 - [2 * (1 - NP1) * (1 - NP2)]
            int overlayedValue;
            if (normalize(p2) <= 0.5)
                overlayedValue = capped(unnormalize(2 * normalize(p1) * normalize(p2)));
            else
                overlayedValue = capped(unnormalize(1 - (2 * (1 - normalize(p1)) * (1 - normalize(p2)))));
            pixels[i][j] = (unsigned char)overlayedValue;
        }
    }
}

void Image::extractRed() {
    for (int i = 0; i < pixelCount; i++) {
        // set every pixel [R, G, B] 
        pixels[i][1] = pixels[i][0]; // Set green channel to red value
        pixels[i][2] = pixels[i][0]; // Set blue channel to red value
    }
}

void Image::extractGreen() {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][0] = pixels[i][1]; // Set red channel to green value
        pixels[i][2] = pixels[i][1]; // Set blue channel to green value
    }
}

void Image::extractBlue() {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][0] = pixels[i][2]; // Set red channel to blue value
        pixels[i][1] = pixels[i][2]; // Set green channel to blue value
    }
}

void Image::addToChannel(int num, int channel) {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][channel] = capped(pixels[i][channel] + num);
    }
}

void Image::multiplyToChannel(int num, int channel) {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][channel] = capped(pixels[i][channel] * num);
    }
}

void Image::combineImages(Image red, Image green, Image blue) {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][0] = red.pixels[i][0];
        pixels[i][1] = green.pixels[i][1];
        pixels[i][2] = blue.pixels[i][2];
    }
}

void Image::flipVertically() {
    vector<vector<unsigned char>> newPixels;
    for (int i = 0; i < pixelCount; i++) {
        newPixels.push_back(pixels[pixels.size() - 1 - i]);
    }
    pixels = newPixels;
}
