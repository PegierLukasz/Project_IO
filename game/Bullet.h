#pragma once

#include "World.h"
#include "Player.h"

class Bullet
{
private:
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;

	sf::Vector2f direction;
	float movementSpeed;

	void initEnemyBallTexture();
	void initEnemyBulletSprite(Enemy* enemy);

	void initPlayerBallTexture();
	void initPlayerBulletSprite(float bullet_size);

public:
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, Enemy* enemy);
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float bullet_size);
	virtual ~Bullet();

	const sf::FloatRect& getBulletBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

