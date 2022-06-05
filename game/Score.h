#pragma once

#include "Menu.h"

class Score
{
private:
	std::vector<int> score;
	sf::Vector2f videoMode;

	int initScores();
	int lookForPlace(int getScore);
	int saveScores();

	sf::Text leaderboardText;
	sf::Text scoreboardText;
	sf::Text scoresText;
	sf::Text topScore;
	sf::Font font;
	sf::RectangleShape scoreboardBackground;
	void initFonts();
	void initText();
	void initScoreboardBackground();
	void renderScoreboardBackground(sf::RenderTarget* target);
	void renderScoreboardText(sf::RenderTarget* target);
	void updateScoreboard(sf::Vector2f position, int score);
	void updateScoreboard(sf::Vector2f position);

public:
	Score();
	~Score();

	bool isNewHighScore(int newScore);
	void pushScore(int getScore);
	void displayScores();
	void render(sf::RenderTarget* target);
	void update(sf::Vector2f position, int score);
	void update(sf::Vector2f position);
	void passVideoMode(float x, float y);
};