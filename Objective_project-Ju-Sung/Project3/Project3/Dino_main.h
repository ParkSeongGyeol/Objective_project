#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include "GameSelector.h"
#include "Scoreboard.h"

using namespace std;
using namespace sf;

const int jumpPixel = 220;

extern int pixels;
extern int frame;
extern int speedgame;
extern int score;

extern bool onGround;
extern bool jump;
extern bool game;
extern bool gameover;

extern Texture DinoT;
extern Texture D_texture;
extern Texture D_End;
extern Texture D_Cactus;
extern Texture D_Restart;
extern Texture D_back;

void restartGame(Sprite& dino, Sprite& cactus);
int DinoGame(RenderWindow& mainWindow);

int pixels = 0;
int frame = 0;
int speedgame = 10;
int score = 0;

bool onGround = true;
bool jump = false;
bool game = false;
bool gameover = false;

Texture DinoT;
Texture D_texture;
Texture D_End;
Texture D_Cactus;
Texture D_Restart;
Texture D_back;

void restartGame(Sprite& dino, Sprite& cactus) {
    game = true;
    dino.setPosition(50, 230);
    cactus.setPosition(-50, 250);
    dino.setTextureRect({ 0,0,44,47 });
    pixels = 0;
    frame = 0;
    speedgame = 10;
    jump = false;
    onGround = true;
    gameover = false;
    score = 0;
}

int DinoGame(RenderWindow& mainWindow) {
    RenderWindow window(VideoMode(1200, 400), "Dino Game");
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("resources/game_font.ttf")) {
        cerr << "Error loading font" << endl;
        return 1;
    }

    DinoT.loadFromFile("resources/dinosaur.png");
    D_texture.loadFromFile("resources/DINO.png");
    D_End.loadFromFile("resources/gameover.png");
    D_Cactus.loadFromFile("resources/cactus.png");
    D_Restart.loadFromFile("resources/restart.png");
    D_back.loadFromFile("resources/back.png");

    Sprite dino(DinoT, { 0,0,44,47 });
    Sprite background(D_texture, { 2,58,600,10 });
    Sprite cactus(D_Cactus);
    Sprite end(D_End);
    Sprite restart(D_Restart);
    Sprite back(D_back);

    dino.setScale(3, 3);
    dino.setPosition(50, 230);
    background.setScale(6, 6);
    background.setPosition(0, 340);
    cactus.setScale(2, 2);
    cactus.setPosition(-50, 250);
    end.setPosition(315, 150);
    end.setScale(3, 3);
    restart.setPosition(620, 220);
    restart.setScale(3, 3);
    back.setPosition(460, 220);
    back.setScale(3, 3);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(window.getSize().x - 1200, 10);

    Clock clock;
    Time elapsed;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    if (!game) {
                        restartGame(dino, cactus);
                    }
                    else if (onGround) {
                        jump = true;
                        onGround = false;
                        pixels = 0;
                        dino.setTextureRect({ 88,0,44,47 });
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (gameover && restart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        restartGame(dino, cactus);
                    }
                    if (gameover && back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        restartGame(dino, cactus);
                        window.close();
                        GameSelector gameSelector;
                        gameSelector.run();
                    }
                }
            }
        }

        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.1 && game && !gameover) {
            score++;
            clock.restart();
        }

        scoreText.setString("Score: " + to_string(score));

        if (!game) {
            window.clear(Color::White);
            window.draw(background);
            window.draw(dino);
            if (gameover) {
                Scoreboard scoreboard;
                scoreboard.addScore("DinoGame", score);
                window.draw(cactus);
                window.draw(end);
                window.draw(restart);
                window.draw(back);
                window.draw(scoreText);
            }
            window.display();
            continue;
        }

        if (jump) {
            if (jumpPixel > pixels) {
                dino.move(0, (-jumpPixel / float(25)));
                pixels += jumpPixel / float(25);
            }
            else {
                jump = false;
                pixels = 0;
            }
        }
        else if (!onGround) {
            if (jumpPixel > pixels) {
                dino.move(0, (jumpPixel / float(25)));
                pixels += jumpPixel / float(25);
            }
            else
                onGround = true;
        }
        else {
            if (frame <= 5) {
                dino.setTextureRect({ 88,0,44,47 });
                frame++;
            }
            else if (frame <= 10) {
                dino.setTextureRect({ 132,0,44,47 });
                frame++;
            }
            else
                frame = 0;
        }

        if (cactus.getPosition().x <= -25) {
            srand(time(NULL));
            cactus.setPosition(1200, 250);
            int random = rand() % 5;
            switch (random) {
            case 0:
                cactus.setTextureRect({ 0,0,25,53 });
                break;
            case 1:
                cactus.setTextureRect({ 25,0,25,53 });
                break;
            case 2:
                cactus.setTextureRect({ 50,0,25,53 });
                break;
            case 3:
                cactus.setTextureRect({ 75,0,25,53 });
                break;
            case 4:
                cactus.setTextureRect({ 100,0,28,53 });
                break;
            }
        }

        cactus.move(-speedgame, 0);
        speedgame += 0.05;

        if (dino.getGlobalBounds().intersects(cactus.getGlobalBounds())) {
            gameover = true;
            game = false;
        }

        window.clear(Color::White);
        window.draw(background);
        window.draw(dino);
        window.draw(cactus);
        window.draw(scoreText);
        window.display();
    }
    return 0;
}