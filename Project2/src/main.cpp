#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extra.h"

using namespace std;

void printHelp() {
    cout << "Project 2: Image Processing, Fall 2023" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}

bool checkTGA(string text) {
    if(text.substr(text.find_last_of(".") + 1) == "tga") {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    string output;
    string source;

    // If no or arguments provided, print help message
    if (argc == 1) {
        printHelp();
        return 0;
    }
    output = argv[1];
    if (output == "--help") {
            printHelp();
            return 0;
        }
    // make sure 1st arg ends in ".tga"
    if (!checkTGA(output)) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    // if 2nd arg DNE
    if (argc == 2) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    source = argv[2];
    // make sure 2nd arg ends in ".tga"
    if (!checkTGA(source)) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    // make sure file exists
    fstream sourceFile(source, ios_base::in | ios_base::binary);
    // if it can't be opened it doesnt exist
    if (!sourceFile.is_open()) {
        cout << "File does not exist." << endl;
        return 0;
    }


    /* 
    The next few arguments describe the first image manipulation method.
    – The third argument will be the name of the first image manipulation method. If this argument is not provided, or if the method does not exist, print "Invalid method name."
    – If the first image manipulation method selected requires additional arguments (such as the "multiply" method, which requires the name of a second file to multiply the first with), then those arguments will be provided after the name of the manipulation algorithm. If the arguments are not provided when they should be, print "Missing argument."
    If the first method selected does not require additional methods (such as the "flip" method), then any following arguments will be related to the next image manipulation algorithm.
    ∗ If the method expects a filename argument, and the argument does not end in .tga, print "Invalid argument, invalid file name." If the file does not exist, print "Invalid argument, file does not exist."
    ∗ If the method expects an integer, but receives something other than an integer, print "Invalid argument, expected number."
    After the first image manipulation method arguments are read, any additional arguments should represent more steps in your program. Unlike the first step, these methods act on the tracking image, and therefore one image supplied to the method will be the output of the previous step.
    – The first argument of successive methods is the name of the image manipulation method. If the method does not exist, print "Invalid method name."
    – Any additional arguments required by the method will be provided next. If an argument is missing, print "Missing argument."
    •
    For commands that are not invalid (commands where some image manipulation is successfully done), the output of the command does not matter. You can print whatever you like!
    Furthermore, your program is expected to return with a return code of zero when no errors occurred in a given command. This just requires you to use return 0; in your main routine when your program completed successfully. You are not expected to return with any specific error code for cases where your command-line interface encountered an error, however, you may find this helpful.
     */
    return 0;
}
