#include "Item.h"

void Item::initItems()
{
	this->item.setRadius(5.f);
	this->item.setFillColor(sf::Color::White);
	this->item.setOutlineThickness(1.f);
	this->item.setOutlineColor(sf::Color::Red);
}

void Item::initHealthItem()
{
	this->item.setFillColor(sf::Color::Green);
	this->item.setOutlineColor(sf::Color::White);
}

void Item::initDamageItem()
{
	this->item.setFillColor(sf::Color::Black);
	this->item.setOutlineColor(sf::Color::White);
}

void Item::initMovementSpeedItem()
{
	this->item.setFillColor(sf::Color::Yellow);
	this->item.setOutlineColor(sf::Color::White);
}

void Item::initFasterShootingItem()
{
	this->item.setFillColor(sf::Color::Blue);
	this->item.setOutlineColor(sf::Color::White);
}

void Item::initBulletSizeItem()
{
	this->item.setFillColor(sf::Color::Red);
	this->item.setOutlineColor(sf::Color::White);
}

void Item::initWallItem()
{
	this->item.setFillColor(sf::Color::White);
	this->item.setOutlineColor(sf::Color::Red);
}

int Item::rollType()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.f, 6.99999f); // From 1 to 6

	float typeF = dist(mt);
	int itemType = static_cast<int>(typeF);

	return itemType;
}

Item::Item(float pos_x, float pos_y)
{
	this->initItems();
	this->item.setPosition(pos_x, pos_y);
	type = this->rollType();

	if (type == 1)
	{
		this->sType = "HealingItem";
		this->initHealthItem();
	}
	else if (type == 2)
	{
		this->sType = "DamagingItem";
		this->initDamageItem();
	}
	else if (type == 3)
	{
		this->sType = "MovementSpeedItem";
		this->initMovementSpeedItem();
	}
	else if (type == 4)
	{
		this->sType = "FasterShootingItem";
		this->initFasterShootingItem();
	}
	else if (type == 5)
	{
		this->sType = "BulletSizeItem";
		this->initBulletSizeItem();
	}
	else if (type == 6)
	{
		this->sType = "WallItem";
			this->initWallItem();
	}
}

Item::~Item()
{
}

const sf::Vector2f& Item::getItemPos() const
{
	return this->item.getPosition();
}

const sf::FloatRect Item::getItemBounds() const
{
	return this->item.getGlobalBounds();
}

std::string Item::getType()
{
	return this->sType;
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->item);
}
