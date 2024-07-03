#include "extra.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Image::Image(string file_path) {
    path = file_path;
    readImageData();
}

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
        // Read header
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
        pixels.resize(pixelCount, vector<unsigned char>(3));

        // Read pixels
        for (int i = 0; i < pixelCount; ++i) {
            file.read(reinterpret_cast<char*>(&pixels[i][2]), 1); // Read blue channel
            file.read(reinterpret_cast<char*>(&pixels[i][1]), 1); // Read green channel
            file.read(reinterpret_cast<char*>(&pixels[i][0]), 1); // Read red channel
        }
        file.close();
    } else {
        cout << "Failed to open the file for reading: " << path << endl;
    }
}

void Image::writeImageData(string output) {
    fstream file(output, ios_base::out | ios_base::binary);
    if (file.is_open()) {
        // Write header
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
        
        // Write pixels
        for (int i = 0; i < pixelCount; ++i) {
            file.write(reinterpret_cast<char*>(&pixels[i][2]), 1); // Write blue channel
            file.write(reinterpret_cast<char*>(&pixels[i][1]), 1); // Write green channel
            file.write(reinterpret_cast<char*>(&pixels[i][0]), 1); // Write red channel
        }
        file.close();
    } else {
        cout << "Failed to open the file for writing: " << output << endl;
    }
}

void Image::multiply(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            int multipliedValue = capped((p1 * p2) / 255);
            pixels[i][j] = (unsigned char)multipliedValue;
        }
    }
}

void Image::screen(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
            int screenedValue = capped(255 - ((255 - p1) * (255 - p2)) / 255);
            pixels[i][j] = (unsigned char)screenedValue;
        }
    }
}

void Image::subtract(Image otherImage) {
    for (int i = 0; i < pixelCount; i++) {
        for (int j = 0; j < 3; j++) {
            int p1 = (int)pixels[i][j];
            int p2 = (int)otherImage.pixels[i][j];
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
            int overlayedValue;
            if (normalize(p2) <= 0.5)
                overlayedValue = capped(unnormalize(2 * normalize(p1) * normalize(p2)));
            else
                overlayedValue = capped(unnormalize(1 - (2 * (1 - normalize(p1) * (1 - normalize(p2))))));
            pixels[i][j] = (unsigned char)overlayedValue;
        }
    }
}

void Image::extractRed() {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][1] = 0; // Set green channel to 0
        pixels[i][2] = 0; // Set blue channel to 0
    }
}

void Image::extractGreen() {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][0] = 0; // Set red channel to 0
        pixels[i][2] = 0; // Set blue channel to 0
    }
}

void Image::extractBlue() {
    for (int i = 0; i < pixelCount; i++) {
        pixels[i][0] = 0; // Set red channel to 0
        pixels[i][1] = 0; // Set green channel to 0
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
    for (int i = 0; i < header.height / 2; ++i) {
        for (int j = 0; j < header.width; ++j) {
            int topIndex = i * header.width + j;
            int bottomIndex = (header.height - i - 1) * header.width + j;
            swap(pixels[topIndex], pixels[bottomIndex]);
        }
    }
}
