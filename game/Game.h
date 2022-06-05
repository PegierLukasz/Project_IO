#pragma once

#include "Player.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::RenderWindow* windowMenu;
	sf::Event windowEvent;
	sf::View view1;

	Player player;
	World world;
	Score scoreboard;

	sf::Vector2f velocity;

	bool gameStart = false;
	bool endGame = false;
	bool pause = false;
	bool exitGame = false;
	int minSpawnChance = 20; // % chance to drop item
	int waveNumber = 1;
	int numberOfEnemies = 1;
	int points;
	bool enemyInRange;
	bool sameMovingDirection = false;

	sf::Clock pauseClock;
	sf::Clock totalTimeClock;
	sf::Clock waveClock;
	sf::Clock duringPauseClock;
	sf::Clock tileSelectorClock;
	sf::Time gameTime;
	sf::Time gamePauseTime;
	sf::Time waveTime;
	bool isWaveClockRestarted = false;
	void restartWaveClock();
	void updateTime();
	sf::Text pauseText;
	void displayPauseText();

	std::vector<Bullet*> enemyBullets;
	std::vector<Bullet*> playerBullets;
	std::vector<Wall*> walls;
	std::vector<Enemy*> enemies;
	std::vector<Item*> items;

	sf::Font font;
	sf::Text endGameText;
	sf::Text endGameText2;
	sf::Text guiText;
	sf::Text guiScoreText;
	sf::Text timerText;
	sf::Text leaderboardText;

	float gridSizeF = 15.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	bool tileSelectorBool;
	void updateTileSelector();
	sf::RectangleShape tileSelector;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	void mainMenuWindow();
	void initVariables();
	void initWindow();
	void initMainMenuWindow();
	void pollEvents();
	void updatePauseInput();
	void updateInput();
	void updateView();

	sf::Vector2f ReturnRandomPositionOnMap();
	void initStaticEnemies(int numberOfEnemies);
	void initFonts();
	void initText();
	void initTileSelector();
	void initWallFences();
	bool checkIfWallCanBePlaced();
	int rollItemSpawn();
	void pickUpItem();
	sf::Vector2f getMultipliedPosition(float pos_x, float pos_y);
	sf::Vector2f getRandomizedPosition(float posx, float posy);

public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	const bool running() const;
	const bool isWaveOver();
	void displayTimer();
	void nextWave();
	void updateTimer();
	void resetVelocity();
	void updateVelocity();
	void updateHUD();
	void updateScoreHud();
	void displayEndGameText();
	void updateWallCollisionWithBullets();
	void updateEnemyBullets();
	void updatePlayerBullets();
	void updatePlayer();
	void updateItems();
	void updateEnemies();
	void updateEnemyAggro();
	void updateWalls();
	void updateWallCollisionWithPlayer();
	void updateWallCollisionWithEnemies();
	void update();
	void render();
	void endGameScreen();
	void displayLeaderboard();
};