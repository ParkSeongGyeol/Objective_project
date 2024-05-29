#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

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
    bool backButtonClicked(Vector2f clickPos); // �ڷ� ���� ��ư�� Ŭ���ߴ��� Ȯ���ϴ� �Լ�
private:
    vector<Score> scores;
    Font font;
    Text titleText;
    Texture backTexture; // �ڷ� ���� ��ư �ؽ�ó
    Sprite backButton; // �ڷ� ���� ��ư ��������Ʈ
};
