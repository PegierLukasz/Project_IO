#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include <iomanip>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	sf::Sprite menuBackgroundSprite;
	sf::Texture menuBackgroundTexture;

	sf::Sprite scoreboardBackgroundSprite;

	void initTexture();
	void initSprite();

public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

	void updateBackground();
	void renderBackground(sf::RenderTarget* target);
	void renderOtherBackground(sf::RenderTarget* target);
};
