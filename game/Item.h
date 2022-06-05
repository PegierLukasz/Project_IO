#pragma once

#include "Score.h"

class Item
{
private:

	int type;
	std::string sType;

	sf::CircleShape item;

	void initItems();
	void initHealthItem();
	void initDamageItem();
	void initMovementSpeedItem();
	void initFasterShootingItem();
	void initBulletSizeItem();
	void initWallItem();

	int rollType();
public:
	Item(float pos_x, float pos_y);
	virtual ~Item();
	const sf::Vector2f& getItemPos() const;
	const sf::FloatRect getItemBounds() const;

	std::string getType();

	void render(sf::RenderTarget* target);

};

