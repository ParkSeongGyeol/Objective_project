#include "Scoreboard.h"

Scoreboard::Scoreboard() {
    if (!font.loadFromFile("resources/game_font.ttf")) {
        cerr << "Error loading font" << endl;
    }
    titleText.setFont(font);
    titleText.setString("Scoreboard");
    titleText.setCharacterSize(40);
    titleText.setFillColor(Color::Black);
    titleText.setPosition(300, 50);

    if (!backTexture.loadFromFile("resources/back.png")) {
        cerr << "Error loading back.png" << endl;
    }
    backButton.setTexture(backTexture);
    backButton.setPosition(20, 20);
    backButton.setScale(2, 2);
}

void Scoreboard::render(RenderWindow& window) {
    window.draw(titleText);

    float y = 150;
    for (const auto& score : scores) {
        Text scoreText(score.name + " - " + to_string(score.score), font, 30);
        scoreText.setFillColor(Color::Black);
        scoreText.setPosition(300, y);
        window.draw(scoreText);
        y += 50;
    }

    window.draw(backButton); // �ڷ� ���� ��ư �׸���
}

void Scoreboard::addScore(const string& name, int score) {
    scores.push_back({ name, score });
    sortScores();
    saveScores();
}

void Scoreboard::loadScores() {
    ifstream file("scores.txt");
    if (!file.is_open()) {
        cerr << "Error opening scores file" << endl;
        return;
    }

    string name;
    int score;
    while (file >> name >> score) {
        scores.push_back({ name, score });
    }

    file.close();
    sortScores();
}

void Scoreboard::saveScores() {
    ofstream file("scores.txt");
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
    sort(scores.begin(), scores.end(), [](const Score& a, const Score& b) {
        return a.score > b.score;
        });
}

bool Scoreboard::backButtonClicked(Vector2f clickPos) {
    return backButton.getGlobalBounds().contains(clickPos); // �ڷ� ���� ��ư�� Ŭ���ߴ��� Ȯ��
}


