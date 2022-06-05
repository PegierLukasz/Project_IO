#include "Menu.h"

Menu::Menu(float width, float height)
{
	this->initTexture();
	this->initSprite();

	if (!this->font.loadFromFile("Fonts/OpenSans-Regular.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2 - 60.f, 400.f));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2 - 90.f, 500.f));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Scoreboard");
	menu[2].setPosition(sf::Vector2f(width / 2 - 112.f, 600.f));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2 - 60.f, 700.f));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::initTexture()
{
	if (this->menuBackgroundTexture.loadFromFile("Textures/menu.jpg") == false)
	{
		std::cout << "MENU::InitTextureError\n";
	}
}

void Menu::initSprite()
{
	this->menuBackgroundSprite.setTexture(this->menuBackgroundTexture);
	this->menuBackgroundSprite.scale(1.f,1.f);
	this->menuBackgroundSprite.setPosition(0.f, 0.f);

	this->scoreboardBackgroundSprite.setTexture(this->menuBackgroundTexture);
	this->scoreboardBackgroundSprite.scale(1.f, 1.f);
	this->scoreboardBackgroundSprite.setPosition(-468.f, -120.f);
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::renderBackground(sf::RenderTarget* target)
{
	target->draw(this->menuBackgroundSprite);
}

void Menu::renderOtherBackground(sf::RenderTarget* target)
{
	target->draw(this->scoreboardBackgroundSprite);
}
