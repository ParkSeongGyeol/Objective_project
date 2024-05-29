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
    bool backButtonClicked(Vector2f clickPos); // 뒤로 가기 버튼을 클릭했는지 확인하는 함수
private:
    vector<Score> scores;
    Font font;
    Text titleText;
    Texture backTexture; // 뒤로 가기 버튼 텍스처
    Sprite backButton; // 뒤로 가기 버튼 스프라이트
};
