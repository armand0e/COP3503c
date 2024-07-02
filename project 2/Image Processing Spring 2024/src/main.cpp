#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extra.h"

using namespace std;

int main() {
    vector<string> files;

    // choose files
    files.push_back("input/car.tga");
    /* files.push_back("input/circles.tga");
    files.push_back("input/layer_blue.tga");
    files.push_back("input/layer_green.tga");
    files.push_back("input/layer_red.tga");
    files.push_back("input/layer1.tga");
    files.push_back("input/layer2.tga");
    files.push_back("input/pattern1.tga");
    files.push_back("input/pattern2.tga");
    files.push_back("input/text.tga");
    files.push_back("input/text2.tga"); */

    for (int i = 0; i < files.size(); i++) {
        // read head
        Image newImage(files[i]);
        newImage.printHeader();
        cout << endl;
        
    }
    return 0;
}
