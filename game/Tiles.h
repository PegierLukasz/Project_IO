#pragma once

#include "TileMap.h"

class Tiles
{
private:
	sf::RectangleShape tileShape;

public:
	Tiles();
	Tiles(float gridSizeF);
	virtual ~Tiles();

	void update();
	void render(sf::RenderTarget* target);
};

