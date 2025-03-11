#pragma once

#include <vector>
#include <SDL3/SDL.h>

struct Tile
{
	int x;
	int y;
	int spriteX;
	int spriteY;
};

class Map
{
private:
	std::vector<Tile> tiles;

public:
	Map();
	~Map();

	void Update(int hoveredX,
		int hoveredY,
		int tileSelectedX,
		int tileSelectedY,
		bool mouseDown);
	void Draw(SDL_Renderer* renderer, SDL_Texture* sprites);
};
