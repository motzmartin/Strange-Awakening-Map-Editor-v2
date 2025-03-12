#pragma once

#include <vector>
#include <SDL3/SDL.h>

struct Tile
{
	int x;
	int y;
	int spriteX;
	int spriteY;
	bool front;
};

class Map
{
private:
	std::vector<Tile> tiles;

public:
	void Update(int hoveredX,
		int hoveredY,
		int tileSelectedX,
		int tileSelectedY,
		bool mouseDown);
	void Draw(SDL_Renderer* renderer, SDL_Texture* sprites, bool behind, int playerY);
	int GetTile(int x, int y, int* tileX, int* tileY);
	void GetFrontTiles(std::vector<SDL_Point>* frontTiles);
	void SwitchFrontTile(int index);
};
