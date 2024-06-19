#ifndef GAMESELECTOR_H
#define GAMESELECTOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class GameSelector {
public:
    GameSelector();
    void run();

private:
    RenderWindow window;
    Font font;
    Text title;
    Text snakeGameButton;
    Text dinoGameButton;
    Text scoreboardButton;

    void setupText(Text& text, const string& str, int size, int x, int y);
    void handleEvents();
    void render();
    void startSnakeGame();
    void startDinoGame();
    void showScoreboard();
    bool isTextClicked(Text& text, Vector2i mousePos);
};

#endif