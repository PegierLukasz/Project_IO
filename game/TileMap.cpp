#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 30.f;
	this->gridSize = 30;
	this->maxSize.x = 100;
	this->maxSize.y = 100;
	this->layers = 5;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tiles>>());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector<Tiles>());

			for(size_t z = 0; z<this->layers;z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tiles(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
			}
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget* target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : x)
			{
				z.render(target);
			}
		}
	}
}
