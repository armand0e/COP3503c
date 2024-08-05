#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cctype>
#include <cmath>

struct digitManager {
    sf::Texture src;
    sf::IntRect digitRect(0,0,21,32);
    sf::Sprite digit;
    digitManager(sf::Texture source) {
        src = source;
        digit.setTexture(src);
        //digitRect.height = src.getSize().y;
        digit.setTextureRect(digitRect);    
    }
    void operator()(int increment) {
        for (int i = 0; i < increment; i++) {
            digit.left += 21;
        }
    }
};

struct Timer {
    int min = 0;
    int sec = 0;
    
}