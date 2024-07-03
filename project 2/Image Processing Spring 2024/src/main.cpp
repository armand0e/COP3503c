#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extra.h"

using namespace std;

int main(int argc, char* argv[]) {
    /* if (argc < 2) {
        // no arguments passed
        throw runtime_error("Error! No arguments given!")
    } 
    else {

    } */
    Image layer1("input/layer1");
    Image pattern1("input/pattern1");
    layer1.multiply(pattern1);
    layer1.writeImageData("output/part1.tga");

    return 0;
}
