#include "World.h"

void World::initTexture()
{
	if (this->worldTexture.loadFromFile("Textures/world.jpg") == false)
	{
		std::cout << "WORLD::InitTextureError\n";
	}
}

void World::initSprite()
{
	this->worldSprite.setTexture(this->worldTexture);
	this->worldSprite.scale(0.5f, 0.5f);
	this->worldSprite.setPosition(0.f, 0.f);
}

World::World()
{
	this->initTexture();
	this->initSprite();
}

World::~World()
{
}

void World::updateWorld()
{
}

void World::renderWorld(sf::RenderTarget* target)
{
	target->draw(this->worldSprite);
}
