#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cctype>
#include <cmath>
#include "Welcome.h"
#include "Game.h"
void Help() {
    std::cout << "Usage:\n\t./sfml-app <path/to/config.cfg>" << std::endl;
}

void print(const std::string& text) {
    std::cout << text;
}

void println(const std::string& text) {
    std::cout << text << std::endl;
}

bool checkCFG(const std::string& text) {
    return text.substr(text.find_last_of(".") + 1) == "cfg";
}

sf::Vector2f round(const sf::Vector2f vector) {
    return sf::Vector2f{ std::round(vector.x+0.5f), std::round(vector.y+0.5f) };
}

int main(int argc, char* argv[]) {
    // CLI
    std::string arg1;
    int rowCount;
    int colCount;
    int mineCount;
    int width;
    int height;
    if (argc == 1) {Help(); return -1;}
    arg1 = argv[1];
    if (arg1 == "--help") {Help(); return -1;}
    if (!checkCFG(arg1)) {println("Invalid file name."); Help(); return -1;}
    std::ifstream config(arg1);
    std::string line;
    if (config.is_open()) {getline(config,line); colCount = stoi(line); getline(config,line); rowCount = stoi(line); getline(config,line); mineCount = stoi(line);}
    else {println("File not found."); return -1;}
    
    // PROGRAM START
    std::string username;

    // Welcome Window
    if(!Welcome(colCount, rowCount, username)) {return -1;}

    // Game Window
    newGame(colCount, rowCount, mineCount, username);

    return 0;
}