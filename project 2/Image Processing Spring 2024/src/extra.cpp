#include "extra.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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
        pixelCount = header.height * header.width;
        // read pixels
        for (int i = 0; i < pixelCount; i++) {
            // each pixel is a vector [B, G, R]
            vector<unsigned char> newPixel;
            for (int j = 0; j < 3; j++) {
                // read each channel
                unsigned char pixelValue;
                file.read(reinterpret_cast<char*>(&pixelValue), 1);
                newPixel.push_back(pixelValue);
            }
            // add the pixel to the list of pixels
            pixels.push_back(newPixel);
        }
    }
}

void Image::writeImageData(string output) {
    fstream file(output, ios_base::out | ios_base::binary);
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
    for (int i = 0; i < pixelCount; i++) {
        // each pixel is a vector [B, G, R]
        for (int j = 0; j < 3; j++) {  
            // write each channel
            file.write(reinterpret_cast<char*>(&pixels[i][j]), 1);
        }
    }
}


void Image::multiply(Image otherImage) {
    // NP1 * NP2
    for (int i = 0; i < pixelCount; i++) {
        // for every single pixel...
        for (int j = 0; j < 3; j++) {
            // for every channel in this pixel
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // manipulate p1 and p2
            int product = capped(normalize(p1) * normalize(p2));
            // apply changes
            pixels[i][j] = (unsigned char)product;
        }
    }
} 

void Image::screen(Image otherImage) {
     for (int i = 0; i < pixelCount; i++) {
        // for every single pixel...
        for (int j = 0; j < 3; j++) {
            // for every channel in this pixel
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // 1 - [(1 - NP1) * (1 - NP2)]
            int screenedValue = capped(1 - ((1 - normalize(p1)) * (1 - normalize(p2))));
            // apply changes to current image
            pixels[i][j] = (unsigned char)screenedValue;
        }
    }
}

void Image::subtract(Image otherImage) {
    // P1 - P2
    for (int i = 0; i < pixelCount; i++) {
        // for every single pixel...
        for (int j = 0; j < 3; j++) {
            // for every channel in this pixel
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // manipulate p1 and p2
            int difference = capped(p1 - p2);
            // apply changes
            pixels[i][j] = (unsigned char)difference;
        }
    }
}

void Image::addition(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        // for every single pixel...
        for (int j = 0; j < 3; j++) {
            // for every channel in this pixel
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // P1 + P2
            int sum = capped(p1 + p2);
            // apply changes
            pixels[i][j] = (unsigned char)sum;
        }
    }
}

void Image::overlay(Image otherImage) {
    // if NP2 <= 0.5: 2 * NP1 * NP2
    // if NP2 > 0.5: 1 - [2 * (1 - NP1) * (1 - NP2)]
    for (int i = 0; i < pixelCount; i++) {
        // for every single pixel...
        for (int j = 0; j < 3; j++) {
            // for every channel in this pixel
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            // manipulate p1 and p2
            int overlayedValue;
            if (normalize(p2) <= 0.5)
                overlayedValue = capped(unnormalize(2 * normalize(p1) * normalize(p2)));
            else
                overlayedValue = capped(unnormalize(1 - (2 * (1 - normalize(p1) * (1 - normalize(p2))))));
            // apply changes
            pixels[i][j] = (unsigned char)overlayedValue;
        }
    }
    
}

Image::Image(string file_path) {
    path = file_path;
    readImageData();
}