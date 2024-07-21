#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

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

int main(int argc, char* argv[]) {
    // CLI
    std::string arg1;
    int rowCount = 25;
    int colCount = 25;
    int width;
    int height;
    if (argc == 1) {Help(); return -1;}
    arg1 = argv[1];
    if (arg1 == "--help") {Help(); return -1;}
    if (!checkCFG(arg1)) {println("Invalid file name."); Help(); return -1;}
    std::ifstream config(arg1);
    std::string line;
    if (config.is_open()) {getline(config,line); rowCount = stoi(line); getline(config,line); colCount = stoi(line);} 
    else {println("File not found."); return -1;}
    
    // PROGRAM START 
    
    // Welcome Window
    width = colCount*32;
    height = (rowCount*32)+100;
    sf::RenderWindow welcome(sf::VideoMode(width, height), "Welcome to Minesweeper!", sf::Style::Close);

    // Welcome Fonts


    while(welcome.isOpen()) {
        sf::Event event;
        while(welcome.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcome.close();
            }
            // handle events here
        }
        const sf::Color welcomeBG = sf::Color(0, 0, 255, 255);
        welcome.clear(welcomeBG);
        // do shit here

        welcome.display();
    }

    // Game Window
    width = colCount*32;
    height = (rowCount*32)+100;
    sf::RenderWindow game(sf::VideoMode(width, height), "Game Window!", sf::Style::Close);

    while(game.isOpen()) {
        sf::Event event;
        while(game.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                game.close();
            }
            // handle events here
        }
        const sf::Color gameBG = sf::Color(255, 255, 255, 255);
        game.clear(gameBG);
        // do shit here
        game.display();
    }

    // Render Window
    //sf::RenderWindow leaderboard(sf::VideoMode(colCount*16, (rowCount*16)+50), "Leaderboard", sf::Style::Close);

    return 0;
}
