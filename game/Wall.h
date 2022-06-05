#pragma once

#include "Enemy.h"

class Wall
{
private:
	sf::RectangleShape wall;
	sf::Vector2u wallGridPos;

	float wallMaxHP;
	float wallHP;
	bool canBeDestroyed;

	void updateWallHealthStatus();
	void initWall();

public:
	Wall(sf::Vector2u pos);
	Wall(sf::Vector2u pos, bool placedByPlayer);
	~Wall();


	const bool isDestroyed();
	const sf::Vector2f& getWallPos() const;
	const sf::FloatRect& getWallBounds() const;
	const sf::Vector2u& getWallGrid() const;

	void render(sf::RenderTarget* target);
	void update();
	void wallTakelDamage(float damage);

};

