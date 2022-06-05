#include "Bullet.h"

void Bullet::initEnemyBallTexture()
{
	if (this->bulletTexture.loadFromFile("Textures/enemyBall.png") == false)
	{
		std::cout << "BULLET::InitTextureError\n";
	}
}

void Bullet::initPlayerBallTexture()
{
	if (this->bulletTexture.loadFromFile("Textures/playerBall.png") == false)
	{
		std::cout << "BULLET::InitTextureError\n";
	}
}

void Bullet::initEnemyBulletSprite(Enemy* enemy)
{
	this->bulletSprite.setTexture(this->bulletTexture);
	this->bulletSprite.scale(enemy->getEnemyBulletSize()*0.04f, enemy->getEnemyBulletSize()*0.04f);
}

void Bullet::initPlayerBulletSprite(float bullet_size)
{
	this->bulletSprite.setTexture(this->bulletTexture);
	this->bulletSprite.scale(bullet_size*0.04f, bullet_size*0.04f);
}

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, Enemy* enemy)
{
	this->initEnemyBallTexture();
	this->initEnemyBulletSprite(enemy);

	this->bulletSprite.setPosition(pos_x - this->getBulletBounds().width / 2, pos_y - this->getBulletBounds().height / 2);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float bullet_size)
{
	this->initPlayerBallTexture();
	this->initPlayerBulletSprite(bullet_size);

	this->bulletSprite.setPosition(pos_x - this->getBulletBounds().width / 2, pos_y - this->getBulletBounds().height / 2);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect& Bullet::getBulletBounds() const
{
	return this->bulletSprite.getGlobalBounds();
}

void Bullet::update()
{
	this->bulletSprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->bulletSprite);
}
