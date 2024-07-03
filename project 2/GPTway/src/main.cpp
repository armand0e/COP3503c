#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extra.h"

using namespace std;

int main(int argc, char* argv[]) {
    //  Use the Multiply blending mode to combine layer1.tga (top layer) with pattern1.tga (bottom layer)
    Image layer1("input/layer1.tga");
    Image pattern1("input/pattern1.tga");
    layer1.multiply(pattern1);
    layer1.writeImageData("output/part1.tga");

    // Use the Subtract blending mode to combine layer2.tga (bottom layer) with car.tga (top layer).
    Image car("input/car.tga");
    Image layer2("input/layer2.tga");
    car.subtract(layer2);
    car.writeImageData("output/part2.tga");

    // Use the Multiply blending mode to combine layer1.tga with pattern2.tga, and store the results temporarily
    Image layer1("input/layer1.tga");
    Image pattern2("input/pattern2.tga");
    layer1.multiply(pattern2);
    // Load the image text.tga and, using that as the bottom layer,
    // combine it with the previous results of layer1/pattern2 using the Screen blending mode
    Image text("input/text.tga");
    layer1.screen(text);
    layer1.writeImageData("output/part3.tga");

    // Multiply layer2.tga with circles.tga, and store it
    Image circles("input/circles.tga");
    Image layer2("input/layer2.tga");
    circles.overlay(pattern3);
    //
    circles.writeImageData("output/part4.tga");

    // Test Add
    Image layer3("input/layer3.tga");
    Image pattern4("input/pattern4.tga");
    layer3.addition(pattern4);
    layer3.writeImageData("output/part5.tga");

    // Test Red Channel Extraction
    Image layer_red("input/layer1.tga");
    layer_red.extractRed();
    layer_red.writeImageData("output/part6.tga");

    // Test Green Channel Extraction
    Image layer_green("input/layer1.tga");
    layer_green.extractGreen();
    layer_green.writeImageData("output/part7.tga");

    // Test Blue Channel Extraction
    Image layer_blue("input/layer1.tga");
    layer_blue.extractBlue();
    layer_blue.writeImageData("output/part8.tga");

    // Test Combine Images
    Image red("input/red.tga");
    Image green("input/green.tga");
    Image blue("input/blue.tga");
    Image combined("output/part9.tga");
    combined.combineImages(red, green, blue);
    combined.writeImageData("output/part9.tga");

    // Test Flip Vertically
    Image layer5("input/layer5.tga");
    layer5.flipVertically();
    layer5.writeImageData("output/part10.tga");

    return 0;
}
