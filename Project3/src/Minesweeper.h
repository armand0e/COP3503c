#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cctype>
#include <cstdlib>
#include <ctime>

struct Tile
{
    int value;
    int row; int col;
    bool isHidden = true;
    bool isFlagged = false;
    bool isDebug = false;
    bool isMine = false;
    bool isNaked = false;
    sf::Vector2f pos;

    Tile(int i, int j , int x, int y)
    {
        value = 8;
        row = i;
        col = j;
        pos.x = x;
        pos.y = y;
    }
    void Draw(sf::RenderWindow& window, std::map<std::string, sf::Texture>& textures)
    {
        sf::Sprite sprite;
        if (isNaked) {
            sprite.setTexture(textures["tile_revealed"]);
        } else {
            if (isHidden)
            {
                if (isFlagged) {
                    sf::Sprite backgroundSprite(textures["tile_hidden"]);
                    backgroundSprite.setPosition(pos.x, pos.y);
                    window.draw(backgroundSprite);
                    sprite.setTexture(textures["flag"]);
                }
                else {
                    sprite.setTexture(textures["tile_hidden"]);
                }

            } else {
                if (value == 0) sprite.setTexture(textures["tile_revealed"]);
                else {
                    sf::Sprite backgroundSprite(textures["tile_revealed"]);
                    backgroundSprite.setPosition(pos.x, pos.y);
                    window.draw(backgroundSprite);
                }
                if (value == 1) sprite.setTexture(textures["number_1"]);
                if (value == 2) sprite.setTexture(textures["number_2"]);
                if (value == 3) sprite.setTexture(textures["number_3"]);
                if (value == 4) sprite.setTexture(textures["number_4"]);
                if (value == 5) sprite.setTexture(textures["number_5"]);
                if (value == 6) sprite.setTexture(textures["number_6"]);
                if (value == 7) sprite.setTexture(textures["number_7"]);
                if (value == 8) sprite.setTexture(textures["number_8"]);
                if (value == 9) sprite.setTexture(textures["mine"]);
            }
        }
        sprite.setPosition(pos.x, pos.y);
        window.draw(sprite);
    }

    bool contains(sf::Vector2i point) {
        return (point.x > pos.x && point.x < pos.x + 32 && point.y > pos.y && point.y < pos.y + 32);
    }
};

struct Board {
    bool paused = false;
    bool debug = false;
    int rowCount; int colCount;
    int mineCount;
    int width; int height;
    std::vector<Tile*> tiles;
    void printValues() {
        for (auto tile : tiles) {
            for (int i = 0; i < colCount; i++) {
                std::cout << tile->value << " ";
            }
            std::cout << std::endl;
        }
    }
    void Draw(sf::RenderWindow& window, std::map<std::string, sf::Texture>& textures) {
       for (auto tile : tiles) {tile->Draw(window,textures);}
    }
    void placeMines() {
        int mines = mineCount;
        std::srand(std::time(0));
        while (mines > 0) {
            int tileCount = rowCount*colCount;
            int randomIndex = std::rand() % tileCount;
            if (!(tiles[randomIndex]->value == 9)) {
                tiles[randomIndex]->value = 9;
                tiles[randomIndex]->isMine = true;
                mines--;
            }
        }
    }
    void generateValues() {
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < colCount; ++col) {
                auto tile = tiles[row * colCount + col];
                if (tile->value == 9) continue; // Skip if it's a mine

                int newValue = 0;

                // Check all 8 neighbors
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        // self check
                        if (i == 0 && j == 0) continue;
                        // either row/col, above/below or left/right
                        int otherRow = row + i;
                        int otherCol = col + j;

                        // check edges
                        if (otherRow >= 0 && otherRow < rowCount && otherCol >= 0 && otherCol < colCount) {
                            if (tiles[otherRow * colCount + otherCol]->value == 9) {
                                newValue++;
                            }
                        }
                    }
                }
                // assign new value
                tile->value = newValue;
            }
        }
    }
    void showMines() {
        for (int i = 0; i < tiles.size(); i++) {
            auto tile = tiles[i];
            if (tile->isHidden && tile->isMine) {tile->isHidden = false; tile->isDebug = true;}
        }
    }
    void hideMines() {
        for (int i = 0; i < tiles.size(); i++) {
            auto tile = tiles[i];
            if (tile->isMine && tile->isDebug) {tile->isHidden = true; tile->isDebug = false;}
        }
    }
    Board(int rows, int cols, int mines) {
        rowCount = rows;
        colCount = cols;
        mineCount = mines;
        int x = 0; int y = 0;
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                Tile* newTile = new Tile(i,j,x,y);
                tiles.push_back(newTile);
                x += 32;
            }
            x = 0; y += 32;
        }
        placeMines();
        generateValues();
    }
    int checkWinner() {
        // 0 = None, 1 = Win, 2 = Lose
        int winCode = 0;
        int valid = 0;
        for (auto tile : tiles) {
            if (!tile->isHidden) {
                if (tile->isMine && !tile->isDebug) {return 2;}
                valid += 1;
            }
        }
        if (valid == tiles.size() - mineCount) {return 1;}
        return 0;
    }
    ~Board() {
        for (auto tile : tiles) {
            delete tile;
        }
    }
};


