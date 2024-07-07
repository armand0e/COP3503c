#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "extra.h"

using namespace std;

void printHelp() {
    cout << "Project 2: Image Processing, Fall 2023" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}

bool checkTGA(const string& text) {
    return text.substr(text.find_last_of(".") + 1) == "tga";
}

bool fileExists(const string& filename) {
    fstream file(filename, ios_base::in | ios_base::binary);
    return file.is_open();
}

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        printHelp();
        return -1;
    }

    string output = argv[1];
    if (strcmp(argv[1], "--help") == 0) {
        printHelp();
        return -1;
    }

    if (!checkTGA(output)) {
        cout << "Invalid file name." << endl;
        return -1;
    }

    if (argc < 3) {
        cout << "Invalid file name." << endl;
        return -1;
    }

    string source = argv[2];
    if (!checkTGA(source)) {
        cout << "Invalid file name." << endl;
        return -1;
    }
    if (!fileExists(source)) {
        cout << "File does not exist." << endl;
        return -1;
    }

    if (argc < 4) {
        cout << "Invalid method name." << endl;
        return -1;
    }

    Image sourceImage(source);
    int methodIndex = 3;

    while (methodIndex < argc) {
        string method = argv[methodIndex];

        if (method == "multiply" || method == "subtract" || method == "overlay" || method == "screen") {
            // error handling
            if (methodIndex + 1 >= argc) {
                cout << "Missing argument." << endl;
                return -1;
            }
            string argFile = argv[methodIndex + 1];
            if (!checkTGA(argFile)) {
                cout << "Invalid argument, invalid file name." << endl;
                return -1;
            }
            if (!fileExists(argFile)) {
                cout << "Invalid argument, file does not exist." << endl;
                return -1;
            }
            // actual method implementation
            if (method == "multiply") {
                
            }
            methodIndex += 2;
        } 
        else if (method == "combine") {
            // error handling
            if (methodIndex + 2 >= argc) {
                cout << "Missing argument." << endl;
                return -1;
            }
            string argFile1 = argv[methodIndex + 1];
            string argFile2 = argv[methodIndex + 2];
            if (!checkTGA(argFile1) || !checkTGA(argFile2)) {
                cout << "Invalid argument, invalid file name." << endl;
                return -1;
            }
            if (!fileExists(argFile1) || !fileExists(argFile2)) {
                cout << "Invalid argument, file does not exist." << endl;
                return -1;
            }
            // actual method implementation
            methodIndex += 3;
        } 
        else if (method == "flip") {
            sourceImage.flipVertically();
            methodIndex += 1;
        } 
        else if (method == "onlyred") {
            sourceImage.extractRed();
            methodIndex += 1;
        } 
        else if (method == "onlygreen") {
            sourceImage.extractGreen();
            methodIndex += 1;
        } 
        else if (method == "onlyblue") {
            sourceImage.extractBlue();
            methodIndex += 1;
        } 
        else if (method == "addred" || method == "addgreen" || method == "addblue" || method == "scalered" || method == "scalegreen" || method == "scaleblue") {
            if (methodIndex + 1 >= argc) {
                cout << "Invalid argument, expected number." << endl;
                return -1;
            }
            string potentialInt = argv[methodIndex + 1];
            try {
                int arg = stoi(potentialInt);
                int channel = (method == "addred" || method == "scalered") ? 0 : (method == "addgreen" || method == "scalegreen") ? 1 : 2;
                if (method.substr(0, 3) == "add") {
                    sourceImage.addToChannel(arg, channel);
                } else {
                    sourceImage.multiplyToChannel(arg, channel);
                }
                methodIndex += 2;
            } catch (invalid_argument&) {
                cout << "Invalid argument, expected number." << endl;
                return -1;
            }
        } 
        else {
            cout << "Invalid method name." << endl;
            return -1;
        }

        sourceImage.writeImageData(output);
    }

    return 0;
}
