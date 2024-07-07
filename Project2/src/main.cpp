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

int main(int argc, const char* argv[]) {
    int methodIndex;
    string output; // arg 1
    string source; // arg 2
    string method; // arg 3


    // If no or arguments provided, print help message
    if (argc == 1) {
        printHelp();
        return -1;
    }
    output = argv[1];
    if (output == "--help") {
            printHelp();
            return -1;
        }
    // make sure 1st arg ends in ".tga"
    if (!checkTGA(output)) {
        cout << "Invalid file name." << endl;
        return -1;
    }
    // if 2nd arg DNE
    if (argc == 2) {
        cout << "Invalid file name." << endl;
        return -1;
    }
    source = argv[2];
    // make sure 2nd arg ends in ".tga"
    if (!checkTGA(source)) {
        cout << "Invalid file name." << endl;
        return -1;
    }
    // make sure file exists
    fstream file(source, ios_base::in | ios_base::binary);
    // if it can't be opened it doesnt exist
    if (!file.is_open()) {
        cout << "File does not exist." << endl;
        return -1;
    }
    // if 3rd arg DNE
    if (argc == 3) {
        cout << "Invalid method name." << endl;
        return -1;
    }
    /* Methods:
    * "multiply":
    * "subtract":
    * "overlay":
    * "screen":
    * "comvine":
    * "flip":
    * "onlyred":
    * "onlygreen":
    * "onlyblue":
    * "addred":
    * "addgreen":
    * "addblue":
    * "scalered":
    * "scalegreen":
    * "scaleblue":

     */
    methodIndex = 3;
    Image sourceImage = Image(source);
    while(true) {
        method = argv[methodIndex];
        /// THESE METHODS REQUIRE TGA ARGUMENTS
        if (method == "multiply") { 
            // 1 arg      
            if (argc-1 <= methodIndex+1) {
                cout << "Missing argument." << endl;
            }
            string other = argv[methodIndex+1];
            if (!checkTGA(other)) {
                cout << "Invalid argument, invalid file name." << endl;
                return -1;
            }
            // make sure file exists
            fstream otherImg(source, ios_base::in | ios_base::binary);
            // if it can't be opened it doesnt exist
            if (!otherImg.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return -1;
            }
        }
        else if (method == "subtract") {
            // 1 arg
            if (argc-1 <= methodIndex+2) {
                cout << "Missing argument." << endl;
            }
        }
        else if (method == "overlay") {
            // 1 arg
            if (argc-1 <= methodIndex+2) {
                cout << "Missing argument." << endl;
            }
        }
        else if (method == "screen") {
            // 1 arg
            if (argc <= methodIndex+2) {
                cout << "Missing argument." << endl;
            }
        }
        else if (method == "combine") {
            // 2 args
            if (argc <= methodIndex+3) {
                cout << "Missing argument." << endl;
            }
        }
        //// THESE METHODS DO NOT USE ANY ARGUMENTS
        else if (method == "flip") {
            sourceImage.flipVertically();
        }
        else if (method == "onlyred") {
            sourceImage.extractRed();
        }    
        else if (method == "onlygreen") {
            sourceImage.extractBlue();
        }
        else if (method == "onlyblue") {
            sourceImage.extractGreen();
        }
        
        //// THESE METHODS REQUIRE INTEGER ARGUMENTS
        else if (method == "addred") {
            if (argc-1 <= methodIndex+2) {
                cout << "Invalid argument, expected number." << endl;
            }
            string potentialInt = argv[methodIndex+1];
            if (!stoi(potentialInt)) {
                cout << "Invalid argument, expected number." << endl;
            }
            int arg = stoi(potentialInt);
            sourceImage.addToChannel(arg, 0);
            methodIndex += 2;
        }
        else if (method == "addgreen") {
            if (argc-1 <= methodIndex+2) {
                cout << "Invalid argument, expected number." << endl;
            }
            string potentialInt = argv[methodIndex+1];
            if (!stoi(potentialInt)) {
                cout << "Invalid argument, expected number." << endl;
            }
            int arg = stoi(potentialInt);
            sourceImage.addToChannel(arg, 1);
            methodIndex += 2;
        }
        else if (method == "addblue") {
            if (argc <= methodIndex+2) {
                cout << "Invalid argument, expected number." << endl;
            }
            string potentialInt = argv[methodIndex+1];
            if (!stoi(potentialInt)) {
                cout << "Invalid argument, expected number." << endl;
            }
            int arg = stoi(potentialInt);
            sourceImage.addToChannel(arg, 2);
            methodIndex += 2;
        }
        else if (method == "scalered") {
            if (argc-1 <= methodIndex+1) {
                cout << "Invalid argument, expected number." << endl;
            }
            string potentialInt = argv[methodIndex+1];
            if (!stoi(potentialInt)) {
                cout << "Invalid argument, expected number." << endl;
            }
            int arg = stoi(potentialInt);
            sourceImage.multiplyToChannel(arg, 0);
            methodIndex += 2;
        }
        else if (method == "scalegreen") {
            if (argc-1 <= methodIndex+1) {
                cout << "Invalid argument, expected number." << endl;
            }
            string potentialInt = argv[methodIndex+1];
            if (!stoi(potentialInt)) {
                cout << "Invalid argument, expected number." << endl;
            }
            int arg = stoi(potentialInt);
            sourceImage.multiplyToChannel(arg, 1);
            methodIndex += 2;
        }
        else if (method == "scaleblue") {
            if (argc <= methodIndex+1) {
                cout << "Invalid argument, expected number." << endl;
            }
            string potentialInt = argv[methodIndex+1];
            if (!stoi(potentialInt)) {
                cout << "Invalid argument, expected number." << endl;
            }
            int arg = stoi(potentialInt);
            sourceImage.multiplyToChannel(arg, 2);
            methodIndex += 2;
        }
        else {
            cout << "Invalid method name." << endl;
            return 0;
        }

        sourceImage.writeImageData(output);
    }    
    cout << "this is the outside" << endl;
    sourceImage.writeImageData(output);
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
