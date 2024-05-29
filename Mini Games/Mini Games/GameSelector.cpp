#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dino_main.h"
#include "Snake_main.h"
#include "Scoreboard.h"
#include "GameSelector.h"

using namespace sf;
using namespace std;

const int M_WIDTH = 800;
const int M_HEIGHT = 600;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 50;

GameSelector::GameSelector() : window(VideoMode(M_WIDTH, M_HEIGHT), "Game Selector") {
    if (!font.loadFromFile("resources/game_font.ttf")) {
        cerr << "Error loading font" << endl;
    }
    setupText(title, "Mini Games", 40, M_WIDTH / 2, M_HEIGHT / 4);
    setupText(snakeGameButton, "Snake Game", 30, M_WIDTH / 2, M_HEIGHT / 2);
    setupText(dinoGameButton, "Dino Game", 30, M_WIDTH / 2, M_HEIGHT / 2 + BUTTON_HEIGHT + 10);
    setupText(scoreboardButton, "Scoreboard", 30, M_WIDTH / 2, M_HEIGHT / 2 + 2 * (BUTTON_HEIGHT + 10));
}

void GameSelector::setupText(Text& text, const string& str, int size, int x, int y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(Color::Black);
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(Vector2f(x, y));
}

void GameSelector::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

void GameSelector::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        else if (event.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(window);
            if (isTextClicked(snakeGameButton, mousePos)) {
                window.close();
                startSnakeGame();
            }
            else if (isTextClicked(dinoGameButton, mousePos)) {
                window.close();
                startDinoGame();
            }
            else if (isTextClicked(scoreboardButton, mousePos)) {
                window.close();
                showScoreboard();
            }
        }
    }
}

bool GameSelector::isTextClicked(Text& text, Vector2i mousePos) {
    FloatRect bounds = text.getGlobalBounds();
    return bounds.contains(static_cast<Vector2f>(mousePos));
}

void GameSelector::render() {
    window.clear(Color::White);
    window.draw(title);
    window.draw(snakeGameButton);
    window.draw(dinoGameButton);
    window.draw(scoreboardButton);
    window.display();
}

void GameSelector::startSnakeGame() {
    cout << "Starting Snake Game..." << endl;
    SnakeGame();  // Snake game logic or function call here
}

void GameSelector::startDinoGame() {
    cout << "Starting Dino Game..." << endl;
    DinoGame(window);  // ���� �޴� �����츦 �μ��� ����
}

void GameSelector::showScoreboard() {
    RenderWindow scoreboardWindow(VideoMode(M_WIDTH, M_HEIGHT), "Scoreboard");
    Scoreboard scoreboard;

    while (scoreboardWindow.isOpen()) {
        Event event;
        while (scoreboardWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                scoreboardWindow.close();
            }
        }

        scoreboardWindow.clear(Color::White);
        scoreboard.render(scoreboardWindow);
        scoreboardWindow.display();
    }
}

int main() {
    HWND hWndConsole = GetConsoleWindow();
    ShowWindow(hWndConsole, SW_HIDE);
    GameSelector gameSelector;
    gameSelector.run();
    return 0;
}
