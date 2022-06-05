#pragma once

#include "Wall.h"

class World
{
private:
	sf::Sprite worldSprite;
	sf::Texture worldTexture;

	float gridSizeF = 15.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);

	void initTexture();
	void initSprite();

public:
	World();
	virtual ~World();

	void updateWorld();
	void renderWorld(sf::RenderTarget* target);

};

