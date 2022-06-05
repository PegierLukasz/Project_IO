#pragma once

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSize;
	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector< Tiles > > > map;
	unsigned layers;

public:
	TileMap();
	virtual ~TileMap();
	void update();
	void render(sf::RenderTarget* target);
};

