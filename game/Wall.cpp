#include "Wall.h"

Wall::Wall(sf::Vector2u pos)
{
	this->canBeDestroyed = false;
	this->wallMaxHP = 5;
	this->wallHP = this->wallMaxHP;
	this->initWall();
	this->wallGridPos = pos;
	this->wall.setPosition(pos.x*15.f, pos.y*15.f);
}

Wall::Wall(sf::Vector2u pos, bool placedByPlayer)
{
	this->canBeDestroyed = true;
	this->wallMaxHP = 5;
	this->wallHP = this->wallMaxHP;
	this->initWall();
	this->wallGridPos = pos;
	this->wall.setPosition(pos.x * 15.f, pos.y * 15.f);
}

void Wall::initWall()
{
	this->wall.setSize(sf::Vector2f(14.f, 14.f));
	this->wall.setFillColor(sf::Color::Red);
	this->wall.setOutlineThickness(1.f);
	this->wall.setOutlineColor(sf::Color::Black);
}

Wall::~Wall()
{
}

const sf::Vector2f& Wall::getWallPos() const
{
	return this->wall.getPosition();
}

const sf::FloatRect& Wall::getWallBounds() const
{
	return this->wall.getGlobalBounds();
}

const sf::Vector2u& Wall::getWallGrid() const
{
	return this->wallGridPos;
}

void Wall::render(sf::RenderTarget* target)
{
	target->draw(this->wall);
}

void Wall::updateWallHealthStatus()
{
	float currentHealth = this->wallHP / this->wallMaxHP;
	if (currentHealth > 0.81)
	{
		this->wall.setFillColor(sf::Color::Color(15, 250, 20, 255));	//GREEN
	}
	if (currentHealth <= 0.81 && canBeDestroyed)
	{
		this->wall.setFillColor(sf::Color::Color(180, 241, 23, 255));	//GREENISH YELLOW
	}
	if (currentHealth <= 0.61 && canBeDestroyed)
	{
		this->wall.setFillColor(sf::Color::Color(252, 186, 3, 255));	//ORANGE
	}
	if (currentHealth <= 0.41 && canBeDestroyed)
	{
		this->wall.setFillColor(sf::Color::Color(252, 102, 3, 255));		//REDISH ORANGE 
	}
	if (currentHealth <= 0.21 && canBeDestroyed)
	{
		this->wall.setFillColor(sf::Color::Color(220, 45, 48, 255));	//RED
	}
}

const bool Wall::isDestroyed()
{
	if (this->wallHP <= 0 && canBeDestroyed) return true;
	return false;
}

void Wall::update()
{
	this->updateWallHealthStatus();
}

void Wall::wallTakelDamage(float damage)
{
	this->wallHP -= damage;
}
