#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <windows.h>

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
int Dino();
