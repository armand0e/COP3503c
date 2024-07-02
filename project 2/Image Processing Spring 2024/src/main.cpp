#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> files;

    // choose files
    files.push_back("input/car.tga");

    for (int i = 0; i < files.size(); i++) {
        // read head
        /*  ID Length 1 byte Denotes the length of the Image ID.
            Color Map Type 1 byte Specifies if a color map is present.
            Image Type 1 byte Indicates the type (e.g., grayscale, true color, compressed).
            Color Map Origin 2 bytes Starting index of the color map, usually 0.
            Color Map Length 2 bytes Length of the color map, usually 0.
            Color Map Depth 1 byte Bit depth of the color map, usually 0.
            X Origin 2 bytes Horizontal image origin, typically 0.
            Y Origin 2 bytes Vertical image origin, usually 0.
            Image Width 2 bytes Width of the image in pixels.
            Image Height 2 bytes Height of the image in pixels.
            Pixel Depth 1 byte Bit depth of each pixel, typically 24 for RGB.
            Image Descriptor 1 byte Provides additional details about the image. */

    }
    return 0;
}
