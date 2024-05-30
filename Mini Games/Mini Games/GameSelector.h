#ifndef GAMESELECTOR_H
#define GAMESELECTOR_H

#include <SFML/Graphics.hpp>
#include "Scoreboard.h"

class GameSelector {
public:
    GameSelector();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    sf::Text snakeGameButton;
    sf::Text dinoGameButton;
    sf::Text scoreboardButton;

    void setupText(sf::Text& text, const std::string& str, int size, int x, int y);
    void handleEvents();
    void render();
    void startSnakeGame();
    void startDinoGame();
    void showScoreboard();
    bool isTextClicked(sf::Text& text, sf::Vector2i mousePos);
};

#endif // GAMESELECTOR_H
