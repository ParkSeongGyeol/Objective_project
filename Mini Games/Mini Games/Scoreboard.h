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
};

class Scoreboard {
public:
    Scoreboard();
    void render(RenderWindow& window);
    void addScore(const string& name, int score);
    void loadScores();
    void saveScores();
    void sortScores();
    void handleEvents();
private:
    vector<Score> scores;
    Font font;
    Text titleText;
    Texture backTexture; // �ڷ� ���� ��ư �ؽ�ó
    Sprite backButton; // �ڷ� ���� ��ư ��������Ʈ
};
