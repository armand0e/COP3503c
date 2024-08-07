#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cctype>
#include <cmath>
#include "Minesweeper.h"
#include "Leaderboard.h"
#include "Timer.h"

void loadAllTextures(std::map<std::string, sf::Texture>& textures)
{
    sf::Texture tile_hidden;
    tile_hidden.loadFromFile("files/images/tile_hidden.png");
    textures.emplace("tile_hidden", tile_hidden);
    sf::Texture tile_revealed;
    tile_revealed.loadFromFile("files/images/tile_revealed.png");
    textures.emplace("tile_revealed", tile_revealed);
    sf::Texture play;
    play.loadFromFile("files/images/play.png");
    textures.emplace("play", play);
    sf::Texture pause;
    pause.loadFromFile("files/images/pause.png");
    textures.emplace("pause", pause);
    sf::Texture digits_sheet;
    digits_sheet.loadFromFile("files/images/digits.png");
    textures.emplace("digits", digits_sheet);
    sf::Texture face_happy;
    face_happy.loadFromFile("files/images/face_happy.png");
    textures.emplace("face_happy", face_happy);
    sf::Texture face_lose;
    face_lose.loadFromFile("files/images/face_lose.png");
    textures.emplace("face_lose", face_lose);
    sf::Texture face_win;
    face_win.loadFromFile("files/images/face_win.png");
    textures.emplace("face_win", face_win);
    sf::Texture debug;
    debug.loadFromFile("files/images/debug.png");
    textures.emplace("debug", debug);
    sf::Texture leaderboard;
    leaderboard.loadFromFile("files/images/leaderboard.png");
    textures.emplace("leaderboard", leaderboard);
    sf::Texture flag;
    flag.loadFromFile("files/images/flag.png");
    textures.emplace("flag", flag);
    sf::Texture mine;
    mine.loadFromFile("files/images/mine.png");
    textures.emplace("mine", mine);
    sf::Texture number_1;
    number_1.loadFromFile("files/images/number_1.png");
    textures.emplace("number_1", number_1);
    sf::Texture number_2;
    number_2.loadFromFile("files/images/number_2.png");
    textures.emplace("number_2", number_2);
    sf::Texture number_8;
    number_8.loadFromFile("files/images/number_8.png");
    textures.emplace("number_8", number_8);
    sf::Texture number_7;
    number_7.loadFromFile("files/images/number_7.png");
    textures.emplace("number_7", number_7);
    sf::Texture number_6;
    number_6.loadFromFile("files/images/number_6.png");
    textures.emplace("number_6", number_6);
    sf::Texture number_5;
    number_5.loadFromFile("files/images/number_5.png");
    textures.emplace("number_5", number_5);
    sf::Texture number_4;
    number_4.loadFromFile("files/images/number_4.png");
    textures.emplace("number_4", number_4);
    sf::Texture number_3;
    number_3.loadFromFile("files/images/number_3.png");
    textures.emplace("number_3", number_3);
}

bool contains(sf::Vector2i& mousePos, sf::Sprite& sprite, int size) {
    return (mousePos.x > sprite.getPosition().x && mousePos.x < sprite.getPosition().x + size && mousePos.y > sprite.getPosition().y && mousePos.y < sprite.getPosition().y + size);
}

void newGame(int colCount, int rowCount, int mineCount, std::string& username) {
    int width = colCount*32;
    int height = (rowCount*32)+100;
    bool firstRun = true;
    sf::RenderWindow game(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);

    // load all textures into texture map
    std::map<std::string, sf::Texture> textures;
    loadAllTextures(textures);
    
    /* // timer digits
    digitManager s1(textures["digits"]);
    digitManager s2(textures["digits"]);
    digitManager m1(textures["digits"]);
    digitManager m2(textures["digits"]); */
    
    //happy button
    sf::Sprite happy(textures["face_happy"]);
    happy.setPosition( ((colCount/2.0f) * 32) - 32, 32 * (rowCount + 0.5f));

    //debug button
    sf::Sprite debug(textures["debug"]);
    debug.setPosition( (colCount * 32) - 304, 32 * (rowCount + 0.5f));

    //pause/play button
    sf::Sprite play_pause(textures["pause"]);
    play_pause.setPosition( (colCount * 32) - 240, 32 * (rowCount + 0.5f));

    //leaderboard button
    sf::Sprite leader(textures["leaderboard"]);
    leader.setPosition( (colCount * 32) - 176, 32 * (rowCount + 0.5f));

    // create game board
    Board* board = new Board(rowCount, colCount, mineCount);
    
    // create counter and timer
    Counter counter(textures["digits"], rowCount, colCount);
    Timer timer(textures["digits"], rowCount, colCount);
    counter.setNum(mineCount);
    timer.setTime(10, 0);
    

    // load leaderboard
    Leaderboard leaderboard(board);
    
    timer.start();
    while(game.isOpen()) {

        sf::Event event;
        while(game.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {game.close();}
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(game);
                if (event.mouseButton.button == sf::Mouse::Left) {    
                    // HAPPY FACE BUTTON
                    if (contains(mousePos, happy, 64)) {
                        timer.reset();
                        board->reset();
                        timer.play(); 
                        board->paused = false; 
                        play_pause.setTexture(textures["pause"]);
                        counter.setNum(mineCount);
                        happy.setTexture(textures["face_happy"]);
                        firstRun = true;
                    }
                    // LEADERBOARD BUTTON
                    if (contains(mousePos, leader, 64)) {
                        timer.stop();
                        leaderboard.Open(game, textures);
                        if (!board->paused) timer.play();
                    }

                    // Buttons that stop at the end of the game:
                    if (board->checkWinner() == 0) {
                        // PAUSE/PLAY BUTTON
                        if (contains(mousePos, play_pause, 64)) {
                            // show pause texture
                            if (!board->paused) {
                                timer.stop(); 
                                board->paused = true; 
                                play_pause.setTexture(textures["play"]);
                                board->getNaked();
                            }  
                            // show play texture
                            else {
                                timer.play(); 
                                board->paused = false; 
                                play_pause.setTexture(textures["pause"]);
                                board->unNaked();
                            }
                        }

                        // Buttons that also stop when paused...
                        if (!board->paused) {
                            // DEBUG BUTTON
                            if (contains(mousePos, debug, 64)) {
                                if (board->debug == false) {board->showMines(); board->debug = true;}
                                else {board->hideMines(); board->debug = false;}
                            }
                            // TILES
                            for (auto tile : board->tiles) {
                                if (tile->contains(mousePos)) {
                                    if (tile->isHidden && !tile->isFlagged) {
                                        board->revealTile(tile->row, tile->col);
                                        // show tile
                                        tile->isHidden = false;

                                        // check all 8 neighbors
                                        for (int i = -1; i <= 1; ++i) {
                                            for (int j = -1; j <= 1; ++j) {
                                                // self check
                                                if (i == 0 && j == 0) continue;
                                                
                                                // either row/col, above/below or left/right
                                                int otherRow = tile->row + i;
                                                int otherCol = tile->col + j;

                                                // check edges
                                                if (otherRow >= 0 && otherRow < rowCount && otherCol >= 0 && otherCol < colCount) {
                                                    if (board->tiles[otherRow * colCount + otherCol]->isEmpty) {
                                                        board->tiles[otherRow * colCount + otherCol]->isHidden = false;
                                                    }
                                                }
                                            }
                                        }           
                                    }
                                }
                            }
                        }
                    }
                }
                // right click
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (board->checkWinner() == 0) { 
                        if (!board->paused) {
                            for (auto tile : board->tiles) {
                                if (tile->contains(mousePos)) {
                                    if (tile->isHidden) {
                                        if (!tile->isFlagged) {
                                            // flag
                                            counter.setNum(counter.num - 1);
                                            tile->isFlagged = true;
                                        }
                                        else {
                                            // unflag
                                            counter.setNum(counter.num + 1);
                                            tile->isFlagged = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        game.clear(sf::Color::White);
        // update and draw timer
        timer.update(); timer.draw(game);
        counter.draw(game);
        // check game over
        if (board->checkWinner() != 0) { 
            // if win
            if (board->checkWinner() == 1) {
                // switch to winner face
                happy.setTexture(textures["face_win"]);
                // stop timer
                timer.stop();
                // check if top time
                if (firstRun) {
                    int minTens = timer.m1.getValue();
                    int minOnes = timer.m2.getValue();
                    int secTens = timer.s1.getValue();
                    int secOnes = timer.s2.getValue();
                    Player current;
                    current.time = std::to_string(minTens) + std::to_string(minOnes) + ":" + std::to_string(secTens) + std::to_string(secOnes);
                    current.name = username;
                    leaderboard.update(current);
                    firstRun = false;
                }
            }
            // if lose
            else if (board->checkWinner() == 2) {
                happy.setTexture(textures["face_lose"]);
                board->showMines();
                timer.stop();
                
            }
        }
        
        
        // draw buttons
        game.draw(happy); game.draw(debug); game.draw(play_pause); game.draw(leader);
        // draw board
        board->Draw(game, textures);
        game.display();
    }
}