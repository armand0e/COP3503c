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
    bool isCurrent = false;
};

struct Leaderboard {
    Board* board;
    bool isOpen;
    std::vector<Player> players;
    int width;
    int height;

    Leaderboard(Board* brd) {
        std::ifstream file("files/leaderboard.txt");
        std::string line;
        players.resize(5);
        if (file.is_open()) {
            std::string name;
            std::string time;
            int index = 0;
            while (getline(file, time, ',') && getline(file, name)) {
                //if (index == 5) break;
                Player newPlayer;
                newPlayer.time = time;
                newPlayer.name = name;        
                players[index] = newPlayer;
                index++;
                
            }
            file.close();
        }
        board = brd;
        width = board->colCount * 16;
        height = (board->rowCount * 16) + 50;
        isOpen = false;
    }
    void update(Player& newPlayer) {
        for (auto& player : players) {
            player.isCurrent = false;
        }

        bool added = false;
        for (int i = 0; i < players.size(); ++i) {
            int currMinutes = std::stoi(players[i].time.substr(0, 2));
            int currSeconds = std::stoi(players[i].time.substr(3, 2));
            int newMinutes = std::stoi(newPlayer.time.substr(0, 2));
            int newSeconds = std::stoi(newPlayer.time.substr(3, 2));

            if (newMinutes < currMinutes || (newMinutes == currMinutes && newSeconds < currSeconds)) {
                if (!added) {
                    players.insert(players.begin() + i, newPlayer);
                    players[i].isCurrent = true;
                    added = true;
                    break;
                }
            }
        }

        // only top 5 
        if (players.size() > 5) {
            players.pop_back();
        }

        // write to leaderboard.txt
        std::ofstream file("files/leaderboard.txt");
        if (file.is_open()) {
            for (int i = 0; i < players.size(); ++i) {
                file << players[i].time << "," << players[i].name;
                if (i < players.size() - 1) file << "\n";
            }
            file.close();
        }
    }
    void Open(sf::RenderWindow& main, std::map<std::string, sf::Texture>& textures) {
        board->getNaked();
        board->Draw(main, textures);
        main.display();
        sf::Font font;
        font.loadFromFile("files/font.ttf");
        
        auto title = sf::Text{"LEADERBOARD", font, 20};
        title.setStyle(sf::Text::Style::Underlined | sf::Text::Style::Bold);
        title.setFillColor(sf::Color::White);
        setText(title, width/2,(height/2)-120);
        
        std::string leaderboardContent;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].isCurrent) {
                leaderboardContent += std::to_string(i + 1) + ".\t" + players[i].time + "\t" + players[i].name + "*";
            }
            else {
                leaderboardContent += std::to_string(i + 1) + ".\t" + players[i].time + "\t" + players[i].name;
            }
            if (i != 4) leaderboardContent += "\n\n";
        }

        // Create sf::Text for the entire leaderboard content
        sf::Text leaderboardText(leaderboardContent, font, 18);
        leaderboardText.setStyle(sf::Text::Bold);
        leaderboardText.setFillColor(sf::Color::White);
    
        // Center-align the text
        setText(leaderboardText, width / 2, (height / 2) + 20);

        sf::RenderWindow window(sf::VideoMode(width, height), "Leaderboard", sf::Style::Close);
        while(window.isOpen()) {
            sf::Event event;
            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    isOpen = false;
                    board->unNaked();
                    board->Draw(main, textures);
                    main.display(); 
                    window.close();
                }
            }
            window.clear(sf::Color::Blue);
            window.draw(title); window.draw(leaderboardText);
            window.display();

        }
    }
    
};