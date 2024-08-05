#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Welcome.h"

struct Player {
    std::string time;
    std::string name;
};

struct Leaderboard {
    Board* board;
    bool isOpen;
    std::vector<Player> players;
    int width;
    int height;
    std::string content;

    Leaderboard(Board* brd) {
        std::ifstream file("files/leaderboard.txt");
        std::string line;
        players.resize(5);
        if (file.is_open()) {
            for (int i = 0; i < 5; i++) {
                getline(file, line);
                Player newPlayer;
                int commaIndex = line.find(',');
                newPlayer.time = line.substr(0, commaIndex);
                newPlayer.name = line.substr(commaIndex+2, line.size());        
                players.push_back(newPlayer);
            }
        }
        board = brd;
        width = board->colCount * 16;
        height = (board->rowCount * 16) + 50;
        isOpen = false;
    }
    void Open() {
        board->getNaked();

        sf::Font font;
        font.loadFromFile("files/font.ttf");
        auto title = sf::Text{"LEADERBOARD", font, 20};
        title.setStyle(sf::Text::Style::Underlined | sf::Text::Style::Bold);
        setText(title, width/2,(height/2)-120);

        auto text = sf::Text{content, font, 18};
        text.setStyle(sf::Text::Style::Bold);
        setText(text, width/2,(height/2)+20);

        sf::RenderWindow window(sf::VideoMode(width, height), "Leaderboard", sf::Style::Close);
        while(window.isOpen()) {
            sf::Event event;
            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    isOpen = false; 
                    window.close();
                }
            }
            window.clear(sf::Color::Blue);

            window.display();

        }
    }
    
};