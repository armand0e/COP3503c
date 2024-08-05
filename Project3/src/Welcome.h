#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cctype>
#include <cmath>
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

std::string capitalizeFirstLetter(const std::string& input) {
    if (input.empty()) {
        return input;
    }

    std::string result = input;
    result[0] = std::toupper(result[0]);

    for (size_t i = 1; i < result.size(); ++i) {
        result[i] = std::tolower(result[i]);
    }

    return result;
}

bool Welcome(int colCount, int rowCount, std::string& username) {
// Welcome Window
    int width = colCount*32;
    int height = (rowCount*32)+100;
    sf::RenderWindow welcome(sf::VideoMode(width, height), "Welcome to Minesweeper!", sf::Style::Close);

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    auto title = sf::Text{"WELCOME TO MINESWEEPER!", font, 24};
    title.setStyle(sf::Text::Style::Underlined | sf::Text::Style::Bold);
    setText(title, width/2,(height/2)-150);
    
    auto text = sf::Text{"Enter you Name:", font, 20};
    text.setStyle(sf::Text::Style::Bold);
    setText(text, width/2,(height/2)-75);

    auto name = sf::Text{"", font, 18};
    name.setFillColor(sf::Color::Yellow);
    name.setStyle(sf::Text::Style::Bold);
    setText(name, width/2,(height/2)-45);

    auto blue = sf::Color(0, 0, 255, 255);
    std::string nameString;

    while(welcome.isOpen()) {
        sf::Event event;
        while(welcome.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcome.close();
                return false;
            }
            // handle events here
            if (event.type == sf::Event::TextEntered) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Backspace)) {
                    if (!nameString.empty()) {
                        nameString.pop_back();
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter)) {
                    if (!nameString.empty()) {
                        username = name.getString();
                        welcome.close(); 
                        break;
                    }
                }
                else if (nameString.size() < 10 && std::isalpha(event.text.unicode)) { // Handle alphabetical characters
                    nameString += static_cast<char>(event.text.unicode);
                }
                nameString = capitalizeFirstLetter(nameString);
                name.setString(nameString);
                setText(name, width/2,(height/2)-45);
            }

        }
        welcome.clear(blue);

        welcome.draw(text); welcome.draw(title); welcome.draw(name);

        welcome.display();
    }
    return true;
}