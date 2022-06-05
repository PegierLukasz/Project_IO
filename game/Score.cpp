#include "Score.h"

int Score::initScores()
{
	std::string filename("Scores/Score.txt", std::ios_base::in);
	std::ifstream readFile(filename);

	readFile.open("Scores/Score.txt");
	if (!readFile.is_open())
	{
		std::cerr << "Could not open the file - '" << filename << "'\n";
		return EXIT_FAILURE;
	}

	int i = 0;
	int topScores;
	while (readFile >> topScores)
	{
		score.push_back(topScores);
		i++;	
	}
	readFile.close();

	return EXIT_SUCCESS;
}

int Score::lookForPlace(int getScore)
{
	int place=0;
	for (int i = 0; i < score.size(); i++)
	{
		if (getScore < score[i])
		{
			place++;
		}
	}
	return place;
}

int Score::saveScores()
{
	std::string filename("Scores/Score.txt", std::ios::trunc);
	std::ofstream readFile(filename);

	int size = score.size();
	int scoreToSave;
	if (size > 10) size--;
	for (int i = 0; i < size; i++)
	{
		scoreToSave = score[i];
		readFile << scoreToSave << std::endl;
	}

	return EXIT_SUCCESS;
}

Score::Score()
{
	this->initFonts();
	this->initText();
	this->initScores();
	this->initScoreboardBackground();
}

Score::~Score()
{
}


bool Score::isNewHighScore(int newScore)
{
	if (score.size() < 10)
	{
		return true;
	}
	for (int i = 0; i < score.size(); i++)
	{
		if (newScore > score[i])
			return true;
	}
	return false;
}

void Score::pushScore(int getScore)
{
	std::stringstream ss4;
	int place = this->lookForPlace(getScore);
	score.insert(score.begin()+(place), getScore);
	this->saveScores();

	ss4 << "NEW TOP SCORE! : " << getScore << " points - " << place+1 << " place at the scoreboard!\n";
	topScore.setString(ss4.str());
}

void Score::displayScores()
{
	std::stringstream ss3;
	ss3 << "------------------------------------------------\n";
	if (score.size() > 10)
	{
		for (int i = 0; i<10; i++)
		{
			ss3 << "TOP " << i+1 << " -> " << score[i] << "\n";
			ss3 << "------------------------------------------------\n";
		}
	}
	else
	{
		for (int i = 0; i < score.size(); i++)
		{
			ss3 << "TOP " << i+1 << " -> " << score[i] << "\n";
			ss3 << "------------------------------------------------\n";
		}
	}

	scoresText.setString(ss3.str());
}

void Score::updateScoreboard(sf::Vector2f position, int score)
{
	this->scoreboardBackground.setSize(sf::Vector2f(this->videoMode.x / 5, this->videoMode.y - this->videoMode.y / 4));
	this->scoreboardBackground.setPosition(position.x-this->scoreboardBackground.getLocalBounds().width/2, position.y-this->scoreboardBackground.getLocalBounds().height/2);
	this->scoreboardText.setPosition(position.x - scoreboardBackground.getLocalBounds().width / 2.5f, position.y + scoreboardBackground.getLocalBounds().height/2.3);
	std::stringstream ss2;
	ss2 << "YOUR SCORE: " << score;

	scoreboardText.setString(ss2.str());

	this->scoresText.setPosition(position.x - scoreboardBackground.getLocalBounds().width/2, position.y - scoreboardBackground.getLocalBounds().height/2.5);

	this->topScore.setPosition(position.x - scoreboardBackground.getLocalBounds().width / 1.5f - scoreboardBackground.getLocalBounds().width, position.y + videoMode.y / 2.5);
	leaderboardText.setCharacterSize(0);
}

void Score::updateScoreboard(sf::Vector2f position)
{
	this->scoreboardBackground.setSize(sf::Vector2f(this->videoMode.x / 5, this->videoMode.y - this->videoMode.y / 4));
	this->scoreboardBackground.setPosition(position.x - this->scoreboardBackground.getLocalBounds().width / 2, position.y - this->scoreboardBackground.getLocalBounds().height / 2);
	this->scoreboardText.setPosition(position.x - scoreboardBackground.getLocalBounds().width / 2.5f, position.y + scoreboardBackground.getLocalBounds().height / 2.3);
	this->scoresText.setPosition(position.x - scoreboardBackground.getLocalBounds().width / 2, position.y - scoreboardBackground.getLocalBounds().height / 2.5);

	this->topScore.setPosition(position.x - scoreboardBackground.getLocalBounds().width / 1.5f - scoreboardBackground.getLocalBounds().width, position.y + videoMode.y / 2.5);

	this->leaderboardText.setPosition(position.x - scoreboardBackground.getLocalBounds().width / 3.f, position.y - scoreboardBackground.getLocalBounds().height / 2.f);
	std::stringstream ss5;
	ss5 << "SCOREBOARD";

	leaderboardText.setString(ss5.str());
}

void Score::render(sf::RenderTarget* target)
{
	this->renderScoreboardBackground(target);
	this->renderScoreboardText(target);
}

void Score::update(sf::Vector2f position, int score)
{
	this->updateScoreboard(position, score);
}

void Score::update(sf::Vector2f position)
{
	this->updateScoreboard(position);
}

void Score::passVideoMode(float x, float y)
{
	this->videoMode.x = x;
	this->videoMode.y = y;
}

void Score::renderScoreboardText(sf::RenderTarget* target)
{
	target->draw(this->scoreboardText);
	target->draw(this->scoresText);
	target->draw(this->topScore);
	target->draw(this->leaderboardText);
}

void Score::initFonts()
{
	if (!this->font.loadFromFile("Fonts/OpenSans-Regular.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}	

void Score::initText()
{
	this->leaderboardText.setCharacterSize(40);
	this->leaderboardText.setFillColor(sf::Color::White);
	this->leaderboardText.setFont(this->font);
	sf::FloatRect textRectx = leaderboardText.getLocalBounds();
	leaderboardText.setOrigin(textRectx.left + textRectx.width / 2.0f,
		textRectx.top + textRectx.height / 2.0f);

	this->scoreboardText.setCharacterSize(35);
	this->scoreboardText.setFillColor(sf::Color::White);
	this->scoreboardText.setFont(this->font);
	sf::FloatRect textRect = scoreboardText.getLocalBounds();
	scoreboardText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	this->scoresText.setCharacterSize(23);
	this->scoresText.setFillColor(sf::Color::White);
	this->scoresText.setFont(this->font);
	sf::FloatRect textRect2 = scoresText.getLocalBounds();
	scoresText.setOrigin(textRect2.left + textRect2.width / 2.0f,
		textRect2.top + textRect2.height/2.0f);

	this->topScore.setCharacterSize(50);
	this->topScore.setFillColor(sf::Color::Green);
	this->topScore.setFont(this->font);
	sf::FloatRect textRect3 = topScore.getLocalBounds();
	topScore.setOrigin(textRect3.left + textRect3.width / 2.0f,
		textRect3.top + textRect3.height / 2.0f);
}

void Score::initScoreboardBackground()
{
	this->scoreboardBackground.setFillColor(sf::Color(50, 50, 50, 200));
	this->scoreboardBackground.setOutlineThickness(1.f);
	this->scoreboardBackground.setOutlineColor(sf::Color::Red);
}

void Score::renderScoreboardBackground(sf::RenderTarget* target)
{
	target->draw(this->scoreboardBackground);
}