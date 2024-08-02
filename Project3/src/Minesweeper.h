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
    bool isDebug = false;
    bool isMine = false;
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
        if (isHidden)
        {
            sprite.setTexture(textures["tile_hidden"]);
        }
        else
        {
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
        sprite.setPosition(pos.x, pos.y);
        window.draw(sprite);

    }
    bool contains(sf::Vector2i point)
    {
        return (point.x > pos.x && point.x < pos.x + 32 && point.y > pos.y && point.y < pos.y + 32);
    }
};

struct Board
{
    bool debug = false;
    int rowCount; int colCount;
    int mineCount;
    int width; int height;
    std::vector<Tile> tiles;
    Board(int rows, int cols, int mines)
    {
        rowCount = rows;
        colCount = cols;
        mineCount = mines;
        int x = 0; int y = 0;
        for (int i = 0; i < rowCount; i++)
        {
            for (int j = 0; j < colCount; j++)
            {
                Tile newTile(i,j,x,y);
                tiles.push_back(newTile);
                x += 32;
            }
            x = 0; y += 32;
        }
    }
    void printValues()
    {
        for (auto tile : tiles)
        {
            for (int i = 0; i < colCount; i++)
            {
                std::cout << tile.value << " ";
            }
            std::cout << std::endl;
        }
    }
    void Draw(sf::RenderWindow& window, std::map<std::string, sf::Texture>& textures)
    {
       for (auto tile : tiles) {tile.Draw(window,textures);}
    }
    void placeMines()
    {
        int mines = mineCount;
        std::srand(std::time(0));
        while (mines > 0)
        {
            int tileCount = rowCount*colCount;
            int randomIndex = std::rand() % tileCount;
            if (!(tiles[randomIndex].value == 9))
            {
                tiles[randomIndex].value = 9;
                tiles[randomIndex].isMine = true;
                mines--;
            }
        }
    }
    void generateValues() {
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < colCount; ++col) {
                Tile& tile = tiles[row * colCount + col];
                if (tile.value == 9) continue; // Skip if it's a mine

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
                            if (tiles[otherRow * colCount + otherCol].value == 9) {
                                newValue++;
                            }
                        }
                    }
                }
                // assign new value
                tile.value = newValue;
            }
        }
    }
    void showMines()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            Tile* tile = &tiles[i];
            if (tile->isHidden && tile->isMine) {tile->isHidden = false; tile->isDebug = true;}
        }
    }
    void hideMines()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            Tile* tile = &tiles[i];
            if (tile->isMine && tile->isDebug) {tile->isHidden = true; tile->isDebug = false;}
        }
    }
};
