#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>

struct digitManager {
    sf::Texture src;
    sf::Sprite digit;
    sf::IntRect digitRect;

    digitManager(sf::Texture& source) : src(source), digitRect(0, 0, 21, 32) {
        digit.setTexture(src);
        digit.setTextureRect(digitRect);
    }

    void setDigit(int value) {
        digitRect.left = value * 21;
        digit.setTextureRect(digitRect);
    }

    void draw(sf::RenderWindow& window, float x, float y) {
        digit.setPosition(x, y);
        window.draw(digit);
    }
    int getValue() {
        return digitRect.left/21;
    }
};

struct Counter {
    int num;
    digitManager ones;
    digitManager tens;
    digitManager hundreds;
    int rowCount;
    int colCount;

    Counter(sf::Texture& digitsTexture, int rows, int cols) : num(0), ones(digitsTexture), tens(digitsTexture), hundreds(digitsTexture), rowCount(rows), colCount(cols) {}

    void setNum(int number) {
        num = number;

        // absolute value
        int absNum = std::abs(num); 
        int h = absNum / 100;
        int t = (absNum / 10) % 10;
        int o = absNum % 10;
        hundreds.setDigit(h);
        tens.setDigit(t);
        ones.setDigit(o);
    }
    void draw(sf::RenderWindow& window) {
        int x = 33;
        int y = 32 * (rowCount + 0.5f) + 16;

        // draw hundreds, tens, and ones digits
        if (hundreds.getValue() != 0) {
            hundreds.draw(window, x, y);
            tens.draw(window, x + 21, y); 
            ones.draw(window, x + 42, y);
        }
        // draw just tens and ones digits
        else {
            tens.draw(window, x, y);
            ones.draw(window, x + 21, y);
        }

        if (num < 0) {
            // draw minus if negative
            sf::Sprite minus(hundreds.src);
            minus.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
            minus.setPosition(12, y);
            window.draw(minus);
        }
    }
};

struct Timer {
    int min;
    int sec;
    digitManager m1;
    digitManager m2;
    digitManager s1;
    digitManager s2;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::seconds pausedDuration;
    bool isRunning;
    int rowCount;
    int colCount;

    Timer(sf::Texture& digitsTexture, int rows, int cols) : min(0), sec(0), m1(digitsTexture), m2(digitsTexture), s1(digitsTexture), s2(digitsTexture), pausedDuration(0), isRunning(false), rowCount(rows), colCount(cols) {}

    void start() {
        if (!isRunning) {
            startTime = std::chrono::high_resolution_clock::now();
            isRunning = true;
        }
    }
    void play() {
        if (!isRunning) {
            startTime = std::chrono::high_resolution_clock::now() - pausedDuration;
            pausedDuration = std::chrono::seconds(0);
            isRunning = true;
        }
    }
    void stop() {
        if (isRunning) {
            pausedDuration += std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime);
            isRunning = false;
        }
    }
    void reset() {
        min = 0;
        sec = 0;
        pausedDuration = std::chrono::seconds(0);
        isRunning = false;
    }
    void update() {
        if (isRunning) {
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
            auto totalSeconds = elapsed.count();
            min = totalSeconds / 60;
            sec = totalSeconds % 60;

            setTime(min, sec);
        }
    }
    void setTime(int minutes, int seconds) {
        min = minutes;
        sec = seconds;

        int absMin = std::abs(min);
        int absSec = std::abs(sec);

        m1.setDigit(absMin / 10);
        m2.setDigit(absMin % 10);
        s1.setDigit(absSec / 10);
        s2.setDigit(absSec % 10);
    }
    void draw(sf::RenderWindow& window) {
        int mx = (colCount * 32) - 97;
        int y = 32 * (rowCount + 0.5f) + 16;
        int sx = (colCount * 32) - 54;

        m1.draw(window, mx, y);
        m2.draw(window, mx + 21, y);
        s1.draw(window, sx, y);
        s2.draw(window, sx + 21, y);
    }
};


