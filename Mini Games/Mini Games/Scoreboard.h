#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

struct Score {
    string name;
    int score;
    string gameName;
};

class Scoreboard {
public:
    Scoreboard();
    void render(RenderWindow& window);
    void addScore(const string& gameName, int score);
    void loadScores();
    void saveScores();
    void sortScores();

private:
    vector<Score> scores;
    Font font;
    Text titleText;
    Texture backTexture;
    Sprite backButton;

    View view;
    float viewOffset;
    const float viewSpeed = 30.0f;
    const string SCORES_FILE = "scores.txt";
};

Scoreboard::Scoreboard() : viewOffset(0) {
    if (!font.loadFromFile("resources/game_font.ttf")) {
        cerr << "Error loading font" << endl;
    }
    titleText.setFont(font);
    titleText.setString("Scoreboard");
    titleText.setCharacterSize(40);
    titleText.setFillColor(Color::Black);
    titleText.setPosition(285, 50);

    if (!backTexture.loadFromFile("resources/back.png")) {
        cerr << "Error loading back.png" << endl;
    }
    backButton.setTexture(backTexture);
    backButton.setPosition(20, 20);
    backButton.setScale(2, 2);

    loadScores();

    view.setSize(800, 600);
    view.setCenter(400, 300);
}

void Scoreboard::render(RenderWindow& window) {
    view.setCenter(400, 300 + viewOffset);

    window.setView(view);
    window.draw(titleText);

    float y = 150;
    for (const auto& score : scores) {
        Text scoreText(score.name + " - " + to_string(score.score), font, 30);
        scoreText.setFillColor(Color::Black);
        scoreText.setPosition(300, y);
        window.draw(scoreText);
        y += 50;
    }

    window.setView(window.getDefaultView());
    window.draw(backButton);

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        else if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                    GameSelector gameSelector;
                    gameSelector.run();
                    return;
                }
            }
        }
        else if (event.type == Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                if (viewOffset > 0) {
                    viewOffset = max(viewOffset - viewSpeed, 0.0f);
                    view.move(0, -viewSpeed);
                }
            }
            else {
                viewOffset += viewSpeed;
                view.move(0, viewSpeed);
            }
        }
    }
}

void Scoreboard::addScore(const string& gameName, int score) {
    for (auto& s : scores) {
        if (s.name == gameName && s.score == score) {
            return; 
        }
    }

    scores.push_back({ gameName, score });
    sortScores();
    saveScores();
}

void Scoreboard::loadScores() {
    ifstream file(SCORES_FILE);
    if (!file.is_open()) {
        cerr << "Error opening scores file" << endl;
        return;
    }

    string gameName;
    int score;
    while (file >> gameName >> score) {
        scores.push_back({ gameName, score });
    }

    file.close();
    sortScores();
}

void Scoreboard::saveScores() {
    ofstream file(SCORES_FILE);
    if (!file.is_open()) {
        cerr << "Error opening scores file" << endl;
        return;
    }

    for (const auto& score : scores) {
        file << score.name << " " << score.score << endl;
    }

    file.close();
}

void Scoreboard::sortScores() {
    sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) { return a.score > b.score; });
}