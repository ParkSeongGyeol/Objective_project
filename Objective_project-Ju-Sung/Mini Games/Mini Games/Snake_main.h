#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include "GameSelector.h"
#include"Snake_main.h"
#include"Dino_main.h"


using namespace sf;
using namespace std;

const int CELL_SIZE = 20;
const int WIDTH = 800;
const int HEIGHT = 600;
const int COLS = WIDTH / CELL_SIZE;
const int ROWS = HEIGHT / CELL_SIZE;

enum Direction { UP, DOWN, LEFT, RIGHT, NONE };
enum GameState { RUNNING, GAME_OVER };


struct SnakeSegment {
    int x, y;
    SnakeSegment(int x, int y) : x(x), y(y) {}
};

class Snake {
public:
    deque<SnakeSegment> body;
    Direction dir;

    Snake(int startX, int startY) {
        body.push_back(SnakeSegment(startX, startY));
        dir = NONE;
    }

    void move() {
        if (dir == NONE) return;

        SnakeSegment newHead = body.front();
        switch (dir) {
        case UP: newHead.y -= 1; break;
        case DOWN: newHead.y += 1; break;
        case LEFT: newHead.x -= 1; break;
        case RIGHT: newHead.x += 1; break;
        default: break;
        }
        body.push_front(newHead);
        if (!ateFood)
            body.pop_back();
        else
            ateFood = false;
    }

    void grow() {
        ateFood = true;
    }

    void changeDirection(Direction newDir) {
        if (dir == NONE || (dir == UP && newDir != DOWN) ||
            (dir == DOWN && newDir != UP) ||
            (dir == LEFT && newDir != RIGHT) ||
            (dir == RIGHT && newDir != LEFT)) {
            dir = newDir;
        }
    }

    bool checkCollision() {
        const SnakeSegment& head = body.front();
        for (size_t i = 1; i < body.size(); ++i) {
            if (head.x == body[i].x && head.y == body[i].y) {
                return true;
            }
        }
        return (head.x < 0 || head.x >= COLS || head.y < 0 || head.y >= ROWS);
    }

private:
    bool ateFood = false;
};

class Game {
public:
    RenderWindow window;
    Snake snake;
    RectangleShape food;
    int foodX, foodY;
    int score;
    GameState gameState;
    Texture gameOverTexture;
    Sprite gameOverSprite;
    Texture restartTexture;
    Sprite restartSprite;
    Texture backgroundTexture;
    Sprite backgroundSprite;

    Game() : window(VideoMode(WIDTH, HEIGHT), "Snake Game"), snake(COLS / 2, ROWS / 2), score(0), gameState(RUNNING) {
        window.setFramerateLimit(10);
        spawnFood();
        loadResources();
    }

    void loadResources() {
        if (!gameOverTexture.loadFromFile("resources/gameover.png")) {
        }
        gameOverSprite.setTexture(gameOverTexture);
        gameOverSprite.setPosition(220, 250);
        gameOverSprite.setScale(2, 2);

        if (!restartTexture.loadFromFile("resources/restart.png")) {
        }
        restartSprite.setTexture(restartTexture);
        restartSprite.setPosition(440,300);
        restartSprite.setScale(2, 2);

        if (!backgroundTexture.loadFromFile("resources/back.png")) {
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(300, 300);
        backgroundSprite.setScale(2, 2);
    }

    void spawnFood() {
        foodX = rand() % COLS;
        foodY = rand() % ROWS;
        food.setPosition(foodX * CELL_SIZE, foodY * CELL_SIZE);
        food.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
        food.setFillColor(Color::Red);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (gameState == RUNNING) {
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::W) {
                        snake.changeDirection(UP);
                    }
                    else if (event.key.code == Keyboard::S) {
                        snake.changeDirection(DOWN);
                    }
                    else if (event.key.code == Keyboard::A) {
                        snake.changeDirection(LEFT);
                    }
                    else if (event.key.code == Keyboard::D) {
                        snake.changeDirection(RIGHT);
                    }
                }
            }
            else if (gameState == GAME_OVER) {
                Scoreboard scoreboard;
                scoreboard.addScore("SnakeGame", score);
                if (event.type == Event::MouseButtonPressed) {
                    if (restartSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        restartGame();
                    }
                    else {
                        window.close();
                        GameSelector gameSelector;
                        gameSelector.run();
                    }
                }
            }
        }
    }

    void update() {
        if (gameState == RUNNING) {
            snake.move();
            if (snake.body.front().x == foodX && snake.body.front().y == foodY) {
                snake.grow();
                spawnFood();
                score++;
            }
            if (snake.checkCollision()) {
                gameState = GAME_OVER;
            }
        }
    }

    void render() {
        window.clear(Color::White);

        if (gameState == GAME_OVER) {
            window.draw(backgroundSprite);
        }

        for (const auto& segment : snake.body) {
            RectangleShape rectangle;
            rectangle.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
            rectangle.setFillColor(Color::Green);
            rectangle.setPosition(segment.x * CELL_SIZE, segment.y * CELL_SIZE);
            window.draw(rectangle);
        }

        window.draw(food);

        Font font;
        if (font.loadFromFile("resources/game_font.ttf")) {
            Text scoreText("Score: " + to_string(score), font, 20);
            scoreText.setFillColor(Color::Black);
            scoreText.setPosition(10, 10);
            window.draw(scoreText);
        }

        if (gameState == GAME_OVER) {
            window.draw(gameOverSprite);
            window.draw(restartSprite);
        }

        window.display();
    }

    void restartGame() {
        snake = Snake(COLS / 2, ROWS / 2);
        score = 0;
        gameState = RUNNING;
        spawnFood();
    }

};

int SnakeGame() {
    Game game;
    game.run();
    return 0;
}