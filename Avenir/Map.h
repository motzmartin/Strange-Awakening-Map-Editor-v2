#pragma once

#include <vector>
#include <SDL3/SDL.h>

struct Tile
{
	SDL_FPoint pos;
	SDL_FPoint sprite;
	bool front;
};

class Map
{
private:
	std::vector<Tile> tiles;

public:
	void Draw(SDL_Renderer* renderer, SDL_Texture* sprites, bool behind, float playerY);

	void AddTile(SDL_FPoint position, SDL_FPoint sprite, bool front);
	void RemoveTile(int index);
	void SwitchFrontTile(int index);

	int GetTile(SDL_FPoint pos, SDL_FPoint* tilePos);
	void GetFrontTiles(std::vector<SDL_FPoint>* frontTiles);
};
