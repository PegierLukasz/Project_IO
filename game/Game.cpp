#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode::getFullscreenModes()[0];
	this->window = new sf::RenderWindow(this->videoMode, "Project_IO", sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
}

void Game::initMainMenuWindow()
{
	this->windowMenu = new sf::RenderWindow(videoMode, "Project_IO_Main_Menu", sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
}

void Game::updateTime()
{
	gameTime = totalTimeClock.getElapsedTime();
	
	sf::Time gameTime2 = gameTime - gamePauseTime;
	//std::cout << gameTime.asSeconds() << " " << gamePauseTime.asSeconds() << " " << gameTime2.asSeconds() << std::endl;

	duringPauseClock.restart();
}

void Game::initVariables()
{
	float viewFromScreen = 5.f;
	this->view1.setSize(sf::Vector2f(this->videoMode.width/viewFromScreen, this->videoMode.height/viewFromScreen));
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/OpenSans-Regular.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Game::initText()
{
	//Gui text init
	this->guiText.setCharacterSize(10);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setFont(this->font);
	this->guiText.setPosition(20.f, 20.f);
	this->guiText.setString("TEST");

	this->endGameText.setCharacterSize(120);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setFont(this->font);
	sf::FloatRect textRect = endGameText.getLocalBounds();
	endGameText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	this->endGameText2.setCharacterSize(120);
	this->endGameText2.setFillColor(sf::Color::Red);
	this->endGameText2.setFont(this->font);
	sf::FloatRect textRect2 = endGameText2.getLocalBounds();
	endGameText2.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);

	this->guiScoreText.setCharacterSize(10);
	this->guiScoreText.setFillColor(sf::Color::White);
	this->guiScoreText.setFont(this->font);
	this->guiScoreText.setPosition(1900.f, 20.f);

	this->timerText.setCharacterSize(10);
	this->timerText.setFillColor(sf::Color::White);
	this->timerText.setFont(this->font);

	this->pauseText.setCharacterSize(20);
	this->pauseText.setFillColor(sf::Color::Black);
	this->pauseText.setFont(this->font);
	this->pauseText.setString("PAUSE");

	this->leaderboardText.setCharacterSize(40);
	this->leaderboardText.setFillColor(sf::Color::White);
	this->leaderboardText.setFont(this->font);
	sf::FloatRect leaderboardRect = leaderboardText.getLocalBounds();
	leaderboardText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void Game::initTileSelector()
{
	this->tileSelector.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileSelector.setFillColor(sf::Color::Transparent);
	this->tileSelector.setOutlineThickness(1.f);
	this->tileSelector.setOutlineColor(sf::Color::Green);
}

void Game::initWallFences()
{
	sf::Vector2u wallPos;
	wallPos.x = 0.f;
	wallPos.y = 0.f;

	for (int i = 0; i < videoMode.width/15.f; i++)
	{
		wallPos.x = i;
		this->walls.push_back(new Wall(wallPos));
	}

	wallPos.x = 0.f;
	wallPos.y = videoMode.height/15.f;
	for (int i = 0; i < videoMode.width/15.f; i++)
	{
		wallPos.x = i;
		this->walls.push_back(new Wall(wallPos));
	}

	wallPos.x = 0.f;
	wallPos.y = 0.f;
	for (int j = 0; j < videoMode.height/15.f; j++)
	{
		wallPos.y = j;
		this->walls.push_back(new Wall(wallPos));
	}
	wallPos.x = videoMode.width/15.f;
	wallPos.y = 0.f;
	for (int j = 0; j <= videoMode.height/15.f; j++)
	{
		wallPos.y = j;
		this->walls.push_back(new Wall(wallPos));
	}
}

int Game::rollItemSpawn()
{
	srand(time(NULL));
	int spawnChance = 1 + rand() % (100/minSpawnChance);
	return spawnChance;
}

void Game::pickUpItem()
{
	for (int i = 0; i < this->items.size(); ++i)
	{
		sf::FloatRect itemBounds = this->items[i]->getItemBounds();
		sf::FloatRect playerBounds = this->player.getGlobalBounds();

		if (playerBounds.intersects(itemBounds))
		{
			std::string type = this->items[i]->getType();
			this->player.giveItem(type);

			this->items.erase(this->items.begin() + i);
			break;
		}
	}
}

sf::Vector2f Game::ReturnRandomPositionOnMap()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist_x(0.f, videoMode.width - 50.f);
	std::uniform_real_distribution<double> dist_y(0.f, videoMode.height - 50.f);

	sf::Vector2f randNum;
	randNum.x = dist_x(mt);
	randNum.y = dist_y(mt);

	return randNum;
}

void Game::initStaticEnemies(int numberOfEnemies)
{
	for (int i = 0; i < numberOfEnemies; i++)
	{
		sf::Vector2f randomPos;
		randomPos = this->ReturnRandomPositionOnMap();
		std::cout << "Enemy spawn at : " << randomPos.x << " " << randomPos.y << "\n";
		this->enemies.push_back(new Enemy(randomPos.x, randomPos.y));
	}
}

sf::Vector2f Game::getMultipliedPosition(float pos_x, float pos_y)
{
	float absPos_x = fabs(pos_x);
	float absPos_y = fabs(pos_y);
	float finalPos = absPos_x * absPos_y;
	float multiplier = 1 / finalPos;

	pos_x *= multiplier;
	pos_y *= multiplier;

	while (fabs(pos_x) + fabs(pos_y) > 1.5f)
	{
		pos_x /= 1.5f;
		pos_y /= 1.5f;
	}
	while (fabs(pos_x) + fabs(pos_y) < 1.3f)
	{
		pos_x *= 1.5f;
		pos_y *= 1.5f;
	}
	sf::Vector2f Position;
	Position.x = pos_x;
	Position.y = pos_y;

	return Position;
}

sf::Vector2f Game::getRandomizedPosition(float pos_x, float pos_y)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(-0.1f, 0.1f);

	pos_x += dist(mt);
	pos_y += dist(mt);

	float absPos_x = fabs(pos_x);
	float absPos_y = fabs(pos_y);
	float finalPos = absPos_x * absPos_y;
	float multiplier = 1 / finalPos;

	pos_x *= multiplier;
	pos_y *= multiplier;

	while (fabs(pos_x) + fabs(pos_y) > 1.0f)
	{
		pos_x /= 1.5f;
		pos_y /= 1.5f;
	}
	while (fabs(pos_x) + fabs(pos_y) < 0.7f)
	{
		pos_x *= 1.5f;
		pos_y *= 1.5f;
	}
	sf::Vector2f Position;
	Position.x = pos_x;
	Position.y = pos_y;

	return Position;
}


//Constructors and Destructors
Game::Game()
{
	this->initWindow();
	this->initMainMenuWindow();
	this->initWallFences();
	this->initStaticEnemies(numberOfEnemies);
	this->initFonts();
	this->initText();
	this->initTileSelector();
}

Game::~Game()
{
	delete this->window;

	//Delete enemyBullets
	for (auto* i : this->enemyBullets)
	{
		delete i;
	}

	for (auto* i : this->playerBullets)
	{
		delete i;
	}

	for (auto* i : this->walls)
	{
		delete i;
	}

	for (auto* i : this->enemies)
	{
		delete i;
	}

	for (auto* i : this->items)
	{
		delete i;
	}
}

//Functions
const bool Game::running() const
{
	return this->window->isOpen();
}

bool Game::checkIfWallCanBePlaced()
{
	for (int i = 0; i < this->walls.size(); ++i)
	{
		if (this->mousePosGrid == this->walls[i]->getWallGrid())
		{
			return false;
		}
	}
	return true;
}

const bool Game::isWaveOver()
{
	if (this->enemies.size() == 0)
	{
		return true;
	}
	return false;
}

void Game::displayTimer()
{
	if (this->waveTime.asSeconds() >= -5)
	{
		this->window->setView(view1);

		std::stringstream ss;
		ss << "Next Wave in: " << std::fixed << std::setprecision(2) << this->waveTime.asSeconds()+5 << "\n";

		this->timerText.setString(ss.str());
	}
	else if (waveTime.asSeconds() < -5)
	{
		std::stringstream ss;
		ss << "";
		this->timerText.setString(ss.str());
	}
}

void Game::nextWave()
{
	if (this->isWaveOver())
	{
		this->waveTime = -waveClock.getElapsedTime();
		this->displayTimer();
		if (!isWaveClockRestarted)
		{
			this->restartWaveClock();
		}
		else if (waveTime.asSeconds() <= -5)
		{
			srand(time(NULL));
			for (int i = 0; i < waveNumber; i++)
			{
				int anotherEnemy = 1 + rand() % (waveNumber + 1 - 1);
				if (anotherEnemy == 1) numberOfEnemies++;
			}
	
			this->waveNumber++;
			this->initStaticEnemies(numberOfEnemies);

			for (int i = 0; i < this->enemies.size(); ++i)
			{
				for (int j = 1; j < waveNumber; j++)
				{
					this->enemies[i]->buffEnemies();
				}
			}

			isWaveClockRestarted = false;
		}
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->windowEvent))
	{
		switch (this->windowEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->windowEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player.movePlayer(-1.f * velocity.x, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player.movePlayer(1.f * velocity.x, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player.movePlayer(0.f, -1.f * velocity.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player.movePlayer(0.f, 1.f * velocity.y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->player.canAttack())
	{
		this->playerBullets.push_back(new Bullet(this->player.getPos().x + this->player.getGlobalBounds().width / 2, this->player.getPos().y, 0.f, -1.f, 4.f, this->player.getPlayerBulletSize()));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->player.canAttack())
	{
		this->playerBullets.push_back(new Bullet(this->player.getPos().x + this->player.getGlobalBounds().width / 2, this->player.getPos().y + this->player.getGlobalBounds().height, 0.f, 1.f, 4.f, this->player.getPlayerBulletSize()));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->player.canAttack())
	{
		this->playerBullets.push_back(new Bullet(this->player.getPos().x, this->player.getPos().y + this->player.getGlobalBounds().height / 2, -1.f, 0.f, 4.f, this->player.getPlayerBulletSize()));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->player.canAttack())
	{
		this->playerBullets.push_back(new Bullet(this->player.getPos().x + this->player.getGlobalBounds().width, this->player.getPos().y + this->player.getGlobalBounds().height / 2, 1.f, 0.f, 4.f, this->player.getPlayerBulletSize()));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->player.getPlaceWallStatus() && this->tileSelectorBool)
	{
		if (this->checkIfWallCanBePlaced())
		{
			this->walls.push_back(new Wall(this->mousePosGrid, true));
			this->player.wallPlaced();
		}
		else std::cout << "There is already a wall!\n";
	}
}

void Game::updateTileSelector()
{
	sf::Time elapsed1 = tileSelectorClock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && elapsed1.asSeconds() >= 1)
	{
		this->tileSelectorBool = !tileSelectorBool;
		tileSelectorClock.restart();
	}
}

void Game::updatePauseInput()
{
	sf::Time elapsed1 = pauseClock.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && elapsed1.asSeconds()>=1)
	{
		this->pause = !pause;
		pauseClock.restart();
	}
	if (pause)
	{
		gamePauseTime = duringPauseClock.getElapsedTime();
		this->displayPauseText();
	}
}

void Game::updateView()
{
	this->view1.setCenter(this->player.getPos().x + this->player.getGlobalBounds().width / 2, this->player.getPos().y + this->player.getGlobalBounds().height / 2);
	this->window->setView(view1);
	this->guiText.setPosition(this->player.getPos().x - view1.getSize().x/2.15, this->player.getPos().y - view1.getSize().y/2.25);
	this->guiScoreText.setPosition(this->player.getPos().x + view1.getSize().x / 3.5, this->player.getPos().y - view1.getSize().y / 2.25);
	this->tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
	this->timerText.setPosition(this->view1.getCenter().x - 40.f, this->player.getPos().y - view1.getSize().y / 2.25);

}

void Game::mainMenuWindow()
{
	Menu menu(windowMenu->getSize().x, windowMenu->getSize().y);
	while (windowMenu->isOpen())
	{

		sf::Event event;

		while (windowMenu->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						this->initVariables();
						gameStart = true;
						windowMenu->close();
						break;
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
						std::cout << "Leaderboard button has been pressed" << std::endl;
						while (true)
						{
							view1.setSize(videoMode.width, videoMode.height);
							windowMenu->setView(view1);
						windowMenu->clear();
						menu.renderOtherBackground(this->windowMenu);
						scoreboard.passVideoMode(this->videoMode.width, this->videoMode.height);
						this->displayLeaderboard();
							this->scoreboard.update(this->view1.getCenter());
							this->scoreboard.render(this->windowMenu);

						scoreboard.displayScores();
						windowMenu->display();
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							this->windowMenu->setView(windowMenu->getDefaultView());
							break;
						}
						}
						break;
					case 3:
						exitGame = true;
						this->window->close();
						windowMenu->close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				exitGame = true;
				this->window->close();
				windowMenu->close();

				break;

			}
		}

		windowMenu->clear();

		menu.renderBackground(this->windowMenu);
		menu.draw(*windowMenu);

		windowMenu->display();
	}
}

void Game::resetVelocity()
{
	this->velocity.x = 1.f;
	this->velocity.y = 1.f;
}

void Game::updateVelocity()
{
	this->resetVelocity();
}

void Game::updateHUD()
{
	this->mousePosWindow = sf::Mouse::getPosition();

	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	if(mousePosView.x>0.f)
		this->mousePosGrid.x = this->mousePosView.x / this->gridSizeU;
	if(mousePosView.y>0.f)
		this->mousePosGrid.y = this->mousePosView.y / this->gridSizeU;
	this->window->setView(view1);

	std::stringstream ss;
	ss << "HP: " << this->player.getPlayerHP() << "\n"
		<< "MovementSpeed: " << this->player.getPlayerMovementSpeed() << "\n"
		<< "Damage: " << this->player.getPlayerDamage() << "\n"
		<< "ReloadTime: " << this->player.getPlayerReloadTime() << "\n"
		<< "BulletSize: " << this->player.getPlayerBulletSize() << "\n";
	guiText.setString(ss.str());
}

void Game::updateScoreHud()
{
	this->window->setView(view1);

	std::stringstream ss;
	ss << "Wave Number: " << waveNumber << "\n"
		<< "Points: " << points << "\n"
		<< "Enemies left: " << enemies.size() << "\n";
	guiScoreText.setString(ss.str());
}

void Game::displayEndGameText()
{
	std::stringstream ss2, ss3;

	this->window->setView(view1);
	this->endGameText.setPosition(this->view1.getCenter().x - view1.getSize().x / 3, this->view1.getCenter().y - 60.f);
	ss2 << "GAME";
	this->endGameText2.setPosition(this->view1.getCenter().x + view1.getSize().x / 6, this->view1.getCenter().y - 60.f);
	ss3 << "OVER";

	endGameText.setString(ss2.str());
	endGameText2.setString(ss3.str());
}

void Game::displayPauseText()
{
	this->window->setView(view1);
	float pauseTextPos_x = this->view1.getCenter().x;
	float pauseTextPos_y = this->view1.getCenter().y;
	this->pauseText.setPosition(pauseTextPos_x - 30.f, pauseTextPos_y - view1.getSize().y / 3);
	std::stringstream ss3;
	ss3 << "PAUSE";

	pauseText.setString(ss3.str());
}

void Game::restartWaveClock()
{
	this->waveClock.restart();
	this->isWaveClockRestarted = true;
}

void Game::updateWallCollisionWithBullets()
{
	for (int i = 0; i < this->walls.size(); ++i)
	{
		for (size_t j = 0; j < this->playerBullets.size(); j++)
		{
			sf::FloatRect wallBounds = this->walls[i]->getWallBounds();
			sf::FloatRect bulletBounds = this->playerBullets[j]->getBulletBounds();

			if (bulletBounds.intersects(wallBounds))
			{
				this->playerBullets.erase(this->playerBullets.begin() + j);
			}
		}

		for (size_t k = 0; k < this->enemyBullets.size(); k++)
		{
			sf::FloatRect wallBounds = this->walls[i]->getWallBounds();
			sf::FloatRect bulletBounds = this->enemyBullets[k]->getBulletBounds();

			if (bulletBounds.intersects(wallBounds))
			{
				this->walls[i]->wallTakelDamage(1.f);
				this->enemyBullets.erase(this->enemyBullets.begin() + k);
				if (this->walls[i]->isDestroyed())
				{
					this->walls.erase(this->walls.begin() + i);
					break;
				}
			}
		}
	}
}

void Game::updateEnemyBullets()
{
	for (auto* bullet : this->enemyBullets)
	{
		bullet->update();
	}
}

void Game::updatePlayerBullets()
{
	for (auto* bullet : this->playerBullets)
	{
		bullet->update();
	}
}

void Game::updatePlayer()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		for (size_t k = 0; k < this->enemyBullets.size(); k++)
		{
			sf::FloatRect playerBounds = this->player.getGlobalBounds();
			sf::FloatRect bulletBounds = this->enemyBullets[k] -> getBulletBounds();

			if (bulletBounds.intersects(playerBounds))
			{
				this->enemyBullets.erase(this->enemyBullets.begin() + k);
				this->player.takeDamage(this->enemies[i]->getEnemyDamage());

				if (this->player.isDead())
				{
					this->endGame = true;
					this->endGameScreen();
					break;
				}
			}
		}
	}
}

void Game::updateItems()
{
	this->pickUpItem();
}

void Game::updateEnemies()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		for (size_t k = 0; k < this->playerBullets.size(); k++)
		{
			if (this->playerBullets[k]->getBulletBounds().intersects(this->enemies[i]->getEnemyBounds()))
			{
				this->playerBullets.erase(this->playerBullets.begin() + k);
				this->enemies[i]->takeDamage(this->player.getPlayerDamage());


				if (this->enemies[i]->isDead())
				{
					int chance = 0;
					chance = this->rollItemSpawn();
					if (chance == 100/minSpawnChance)
					{
						this->items.push_back(new Item(this->enemies[i]->getEnemyPos().x, this->enemies[i]->getEnemyPos().y));
					}

					this->enemies.erase(this->enemies.begin() + i);
					points += 100*waveNumber/5;
					break;
				}
			}
		}
	}
	for (auto* enemy : this->enemies)
	{
		enemy->update();
	}
}

void Game::updateEnemyAggro()
{
		for (int i = 0; i < this->enemies.size(); ++i)
		{
			this->enemies[i]->setRangeFalse();

			float enemyPosition_x = enemies[i]->getEnemyBounds().left + enemies[i]->getEnemyBounds().width / 2;
			float enemyPosition_y = enemies[i]->getEnemyBounds().top + enemies[i]->getEnemyBounds().height / 2;
			float playerPosition_x = player.getGlobalBounds().left + player.getGlobalBounds().width / 2;
			float playerPosition_y = player.getGlobalBounds().top + player.getGlobalBounds().height / 2;
			float maxDistance_y = this->enemies[i]->getEnemyRange();
			float maxDistance_x = maxDistance_y * 1.5;

			//TOP LEFT // -X -Y CORDS
			if (enemyPosition_x < playerPosition_x && enemyPosition_x > playerPosition_x - maxDistance_x && enemyPosition_y < playerPosition_y && enemyPosition_y > playerPosition_y - maxDistance_y)
			{
				if (!this->enemies[i]->checkIfInRange())	this->enemies[i]->setRange();

				sf::Vector2f playerPos = this->player.getPos();
				float pos_x = (playerPos.x - this->enemies[i]->getEnemyPos().x) / 100;
				float pos_y = (playerPos.y - this->enemies[i]->getEnemyPos().y) / 100;

				if (enemies[i]->canAttack())
				{
					if (pos_x && pos_y != 0)
						{
							sf::Vector2f positionToHit = getMultipliedPosition(pos_x, pos_y);
							this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, positionToHit.x, positionToHit.y, 3.f, this->enemies[i]));
						}
					else this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, pos_x, pos_y, 3.f, this->enemies[i]));
				}
			}
			//DOWN LEFT // -X +Y CORDS
			if (enemyPosition_x < playerPosition_x && enemyPosition_x > playerPosition_x - maxDistance_x && enemyPosition_y > playerPosition_y && enemyPosition_y - maxDistance_y < playerPosition_y)
			{
				if (!this->enemies[i]->checkIfInRange())	this->enemies[i]->setRange();

				sf::Vector2f playerPos = this->player.getPos();
				float pos_x = (playerPos.x - this->enemies[i]->getEnemyPos().x) / 100;
				float pos_y = (playerPos.y - this->enemies[i]->getEnemyPos().y) / 100;

				if (enemies[i]->canAttack())
				{
					if (pos_x && pos_y != 0)
					{
						sf::Vector2f positionToHit = getMultipliedPosition(pos_x, pos_y);
						this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, positionToHit.x, positionToHit.y, 3.f, this->enemies[i]));
					}
					else this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, pos_x, pos_y, 3.f, this->enemies[i]));
				}
			}
			//TOP RIGHT // +X -Y CORDS
			if (enemyPosition_x > playerPosition_x && enemyPosition_x - maxDistance_x < playerPosition_x && enemyPosition_y < playerPosition_y && enemyPosition_y + maxDistance_y > playerPosition_y)
			{
				if (!this->enemies[i]->checkIfInRange())	this->enemies[i]->setRange();

				sf::Vector2f playerPos = this->player.getPos();
				float pos_x = (playerPos.x - this->enemies[i]->getEnemyPos().x) / 100;
				float pos_y = (playerPos.y - this->enemies[i]->getEnemyPos().y) / 100;

				if (enemies[i]->canAttack())
				{
					if (pos_x && pos_y != 0)
					{
						sf::Vector2f positionToHit = getMultipliedPosition(pos_x, pos_y);
						this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, positionToHit.x, positionToHit.y, 3.f, this->enemies[i]));
					}
					else this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, pos_x, pos_y, 3.f, this->enemies[i]));
				}
			}
			//DOWN RIGHT // +X +Y CORDS
			if (enemyPosition_x > playerPosition_x && enemyPosition_x - maxDistance_x < playerPosition_x && enemyPosition_y > playerPosition_y && enemyPosition_y - maxDistance_y < playerPosition_y)
			{
				if(!this->enemies[i]->checkIfInRange())	this->enemies[i]->setRange();

				sf::Vector2f playerPos = this->player.getPos();
				float pos_x = (playerPos.x - this->enemies[i]->getEnemyPos().x) / 100;
				float pos_y = (playerPos.y - this->enemies[i]->getEnemyPos().y) / 100;

				if (enemies[i]->canAttack())
				{
					if (pos_x && pos_y != 0)
					{
						sf::Vector2f positionToHit = getMultipliedPosition(pos_x, pos_y);
						this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, positionToHit.x, positionToHit.y, 3.f, this->enemies[i]));
					}
					else this->enemyBullets.push_back(new Bullet(this->enemies[i]->getEnemyPos().x + this->enemies[i]->getEnemyBounds().width/2, this->enemies[i]->getEnemyPos().y + this->enemies[i]->getEnemyBounds().height/2, pos_x, pos_y, 3.f, this->enemies[i]));
				}
			}
			
			if (!this->enemies[i]->checkIfInRange())
			{
				sf::Vector2f playerPos = this->player.getPos();
				float pos_x = (playerPos.x - this->enemies[i]->getEnemyPos().x) / 100;
				float pos_y = (playerPos.y - this->enemies[i]->getEnemyPos().y) / 100;
				if (pos_x && pos_y != 0)
				{
					sf::Vector2f positionToMove = getRandomizedPosition(pos_x, pos_y);
					this->enemies[i]->moveEnemy(positionToMove.x/2, positionToMove.y/2);
				}
			}
		}
}

void Game::updateWallCollisionWithPlayer()
{
	for (auto* wall : this->walls)
	{
		sf::FloatRect wallBounds = wall->getWallBounds();
		sf::FloatRect playerBounds = player.getGlobalBounds();
		sf::FloatRect nextPos = playerBounds;

		nextPos.left += velocity.x;
		nextPos.top += velocity.y;

		if (wallBounds.intersects(nextPos))	
		{
			float intersectValueX = (playerBounds.left + playerBounds.width / 2) - (wallBounds.left + wallBounds.width / 2);
			float intersectValueY = (playerBounds.top + playerBounds.height / 2) - (wallBounds.top + wallBounds.height / 2);

			//TOP & BOTTOM
			if (fabs(intersectValueY)>fabs(intersectValueX))
			{
				if (intersectValueY < 0)
				{
					velocity.y = 0.f;
					player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				else
				{
					velocity.y = 0.f;
					player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}
			}
			
			//LEFT & RIGHT COLLISION
			else if (fabs(intersectValueX) > fabs(intersectValueY))
			{
				if (intersectValueX < 0)
				{
					velocity.x = 0.f;
					player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}
				else
				{
					velocity.x = 0.f;
					player.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}
			}
		}
	}
}

void Game::updateWalls()
{
	for (auto* wall : this->walls)
	{
		wall->update();
	}
}

void Game::updateWallCollisionWithEnemies()
{
	for (auto* wall : this->walls)
	{
		for (int i = 0; i < this->enemies.size(); ++i)
		{
			float enemyPosition_x = this->enemies[i]->getEnemyBounds().left + enemies[i]->getEnemyBounds().width / 2;
			float enemyPosition_y = this->enemies[i]->getEnemyBounds().top + enemies[i]->getEnemyBounds().height / 2;

			sf::FloatRect wallBounds = wall->getWallBounds();
			sf::FloatRect enemyBounds = this->enemies[i]->getEnemyBounds();
			sf::FloatRect nextPos = enemyBounds;

			nextPos.left += velocity.x;
			nextPos.top += velocity.y;

			if (wallBounds.intersects(nextPos))
			{
				float intersectValueX = (enemyBounds.left + enemyBounds.width / 2) - (wallBounds.left + wallBounds.width / 2);
				float intersectValueY = (enemyBounds.top + enemyBounds.height / 2) - (wallBounds.top + wallBounds.height / 2);

				//TOP & BOTTOM
				if (fabs(intersectValueY) > fabs(intersectValueX))
				{
					if (intersectValueY < 0)
					{
						velocity.y = 0.f;
						this->enemies[i]->setEnemyPosition(enemyBounds.left, wallBounds.top - enemyBounds.height);
					}
					else
					{
						velocity.y = 0.f;
						this->enemies[i]->setEnemyPosition(enemyBounds.left, wallBounds.top + wallBounds.height);
					}
				}

				//LEFT & RIGHT COLLISION
				else if (fabs(intersectValueX) > fabs(intersectValueY))
				{
					if (intersectValueX < 0)
					{
						velocity.x = 0.f;
						this->enemies[i]->setEnemyPosition(wallBounds.left - enemyBounds.width, enemyBounds.top);
					}
					else
					{
						velocity.x = 0.f;
						this->enemies[i]->setEnemyPosition(wallBounds.left + wallBounds.width, enemyBounds.top);
					}
				}
			}
		}
	}
}

void Game::update()
{
	if (!endGame && !pause && gameStart)
	{
		this->updateTime();
		this->pollEvents();
		this->updateInput();
		this->updatePauseInput();
		this->updateTileSelector();
		this->updatePlayer();
		this->updateEnemies();
		this->updateWalls();
		this->updateEnemyAggro();
		this->updateEnemyBullets();
		this->updatePlayerBullets();
		this->updateWallCollisionWithPlayer();
		this->updateWallCollisionWithEnemies();
		this->updateWallCollisionWithBullets();
		this->updateVelocity();

		this->updateView();
		this->player.update();
		this->updateHUD();
		this->updateScoreHud();
	
		this->updateItems();
		this->nextWave();
	}
	else if(!endGame && pause)
	{
		this->updatePauseInput();
		this->updateHUD();
		this->pollEvents();
		this->player.update();
	}
	else if(endGame)
	{
		this->pollEvents();
		this->scoreboard.update(this->view1.getCenter(), points);
	}
	else if (!gameStart && !exitGame)
	{
		this->mainMenuWindow();
	}
}

void Game::render()
{
	if (!this->endGame && gameStart)
	{
		this->window->clear();

		this->world.renderWorld(this->window);

		//Render

		for (auto* bullet : this->enemyBullets)
		{
			bullet->render(this->window);
		}
		for (auto* bullet : this->playerBullets)
		{
			bullet->render(this->window);
		}
		for (auto* wall : this->walls)
		{
			wall->render(this->window);
		}
		for (auto* enemy : this->enemies)
		{
			enemy->render(this->window);
		}
		for (auto* item : this->items)
		{
			item->render(this->window);
		}

		//Render gui
		this->window->draw(this->guiText);
		this->window->draw(this->guiScoreText);
		this->window->draw(this->timerText);

		if (this->player.getPlaceWallStatus() && this->tileSelectorBool)
			this->window->draw(this->tileSelector);

		if (this->pause)
			this->window->draw(this->pauseText);

		this->player.render(this->window);

		this->window->display();
	}
	//END GAME
	if (this->endGame)
	{
		this->window->clear();

		this->window->draw(this->endGameText);
		this->window->draw(this->endGameText2);
		this->scoreboard.render(this->window);
		this->window->draw(this->leaderboardText);

		this->window->display();
	}

}

void Game::displayLeaderboard()
{
	window->setView(view1);
	leaderboardText.setPosition(view1.getCenter().x-view1.getSize().x/14, view1.getCenter().y - view1.getSize().y / 2.7f);

	std::stringstream ss2;
	ss2 << "SCOREBOARD";

	leaderboardText.setString(ss2.str());
}

void Game::endGameScreen()
{
	view1.setSize(this->videoMode.width, this->videoMode.height);
	window->setView(view1);
	displayEndGameText();
	if (scoreboard.isNewHighScore(this->points))
	{
		scoreboard.pushScore(this->points);
		scoreboard.displayScores();
	}	
	scoreboard.passVideoMode(this->videoMode.width, this->videoMode.height);
	this->displayLeaderboard();
	scoreboard.displayScores();
}