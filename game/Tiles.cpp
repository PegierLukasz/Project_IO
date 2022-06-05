#include "Tiles.h"

Tiles::Tiles()
{

}

Tiles::Tiles(float gridSizeF)
{
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileShape.setFillColor(sf::Color::White);
}

Tiles::~Tiles()
{
}

void Tiles::update()
{
}

void Tiles::render(sf::RenderTarget* target)
{
	target->draw(this->tileShape);
}
