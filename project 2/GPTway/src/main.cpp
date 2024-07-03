#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extra.h"

using namespace std;

int main(int argc, char* argv[]) {
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            //  Use the Multiply blending mode to combine layer1.tga (top layer) with pattern1.tga (bottom layer)
            Image layer1("input/layer1.tga");
            Image pattern1("input/pattern1.tga");
            layer1.multiply(pattern1);
            layer1.writeImageData("output/part1.tga");
        }
        else if (i == 1) {
            // Use the Subtract blending mode to combine layer2.tga (bottom layer) with car.tga (top layer).
            Image car("input/car.tga");
            Image layer2("input/layer2.tga");
            car.subtract(layer2);
            car.writeImageData("output/part2.tga");
        }
        else if (i == 2) {
            // Use the Multiply blending mode to combine layer1.tga with pattern2.tga, and store the results temporarily
            Image layer1("input/layer1.tga");
            Image pattern2("input/pattern2.tga");
            layer1.multiply(pattern2);
            // Load the image text.tga and, using that as the bottom layer,
            // combine it with the previous results of layer1/pattern2 using the Screen blending mode
            Image text("input/text.tga");
            layer1.screen(text);
            layer1.writeImageData("output/part3.tga");
        }
        else if (i == 3) {
            // Multiply layer2.tga with circles.tga, and store it
            Image circles("input/circles.tga");
            Image layer2("input/layer2.tga");
            circles.multiply(layer2);
            // Load pattern2.tga as the bottom layer, combine it with the previous result using the Subtract blending mode.
            Image pattern2("input/pattern2.tga");
            circles.subtract(pattern2);
            circles.writeImageData("output/part4.tga");
        }
        else if (i == 4) {
            // Combine layer1.tga (as the top layer) with pattern1.tga using the Overlay blending mode.
            Image layer1("input/layer1.tga");
            Image pattern1("input/pattern1.tga");
            layer1.overlay(pattern1);
            layer1.writeImageData("output/part5.tga");
        }
        else if (i == 5) {
            // Load car.tga and add 200 to the green channel
            Image car("input/car.tga");
            car.addToChannel(200, 1);
            car.writeImageData("output/part6.tga");
        }
        else if (i == 6) {
            // Load car.tga and scale (multiply) the red channel by 4, and the blue channel by 0
            Image car("input/car.tga");
            car.multiplyToChannel(4, 0);
            car.multiplyToChannel(0, 2);
            car.writeImageData("output/part7.tga");
            // Wrong!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        else if (i == 7) {
            // Load car.tga and write each channel to a separate file: the red channel should be part8_r.tga,
            // the green channel should be part8_g.tga, and the blue channel should be part8_b.tga
            Image carRed("input/car.tga");
            Image carGreen("input/car.tga");
            Image carBlue("input/car.tga");
            carBlue.extractBlue();
            carGreen.extractGreen();
            carRed.extractRed();
            carRed.writeImageData("output/part8_r.tga");
            carGreen.writeImageData("output/part8_g.tga");
            carBlue.writeImageData("output/part8_b.tga");
        }
        else if (i == 8) {
            // Load layer_red.tga, layer_green.tga and layer_blue.tga, and combine the three files
            Image red("input/layer_red.tga");
            Image green("input/layer_green.tga");
            Image blue("input/layer_blue.tga");
            red.combineImages(red, green, blue);
            red.writeImageData("output/part9.tga");
        }
        else if (i == 9) {
            // Test Flip Vertically
            Image text2("input/text2.tga");
            text2.flipVertically();
            text2.writeImageData("output/part10.tga");
            // wrong
        }
    }
    return 0;
}
