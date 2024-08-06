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

void resetBoard(Board* board) {
    Board* tmp = board;
    board = new Board(board->rowCount, board->colCount, board->mineCount);
    delete tmp;
}

void newGame(int colCount, int rowCount, int mineCount, std::string& username) {
    int width = colCount*32;
    int height = (rowCount*32)+100;
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
    
    // load leaderboard
    Leaderboard leaderboard(board);

    while(game.isOpen()) {
        sf::Event event;
        while(game.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {game.close();}
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(game);
                if (event.mouseButton.button == sf::Mouse::Left) {    
                    // HAPPY FACE BUTTON
                    if (contains(mousePos, happy, 64)) {
                        resetBoard(board);
                    }
                    // LEADERBOARD BUTTON
                    if (contains(mousePos, leader, 64)) {
                        leaderboard.Open(game, textures);
                    }

                    // Buttons that stop at the end of the game
                    
                    if (board->checkWinner() == 0) {
                        // PAUSE/PLAY BUTTON
                        if (contains(mousePos, play_pause, 64)) {
                            // show pause texture
                            if (!board->paused) {board->paused = true; play_pause.setTexture(textures["play"]);}  
                            // show play texture
                            else {board->paused = false; play_pause.setTexture(textures["pause"]);}
                        }

                        // Buttons that stop when paused...
                        if (!board->paused) {
                            // DEBUG BUTTON
                            if (contains(mousePos, debug, 64)) {
                                if (board->debug == false) {board->showMines(); board->debug = true;}
                                else {board->hideMines(); board->debug = false;}
                            }
                            // TILES
                            for (auto tile : board->tiles) {
                                if (tile->contains(mousePos)) {
                                    if (tile->isHidden) tile->isHidden = false;
                                }
                            }
                        }
                    }
                }
                // flag tiles               
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (board->checkWinner() == 0) { 
                        if (!board->paused) {
                            for (auto tile : board->tiles) {
                                if (tile->contains(mousePos)) {
                                    if (tile->isHidden) {
                                        if (!tile->isFlagged) tile->isFlagged = true;
                                        else {tile->isFlagged = false;}
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        game.clear(sf::Color::White);
        
        
        // check game over
        if (board->checkWinner() != 0) { 
            // if win
            if (board->checkWinner() == 1) {
                // switch to winner face
                happy.setTexture(textures["face_win"]);
                // stop timer

                // check if top time
                
            }
            // if lose
            else if (board->checkWinner() == 2) {
                happy.setTexture(textures["face_lose"]);
            }
            // open leaderboard
            leaderboard.Open(game, textures);
            
        }
        
        
        // draw buttons
        game.draw(happy); game.draw(debug); game.draw(play_pause); game.draw(leader);
        // draw board
        board->Draw(game, textures);
        game.display();
    }
}