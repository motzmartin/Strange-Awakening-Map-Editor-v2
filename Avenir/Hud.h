#pragma once

#include <SDL3/SDL.h>

class Hud
{
private:
	int hoveredX = 0;
	int hoveredY = 0;

	int tileSelectedX = 0;
	int tileSelectedY = 0;

	bool inventory = false;

public:
	void Update(int mouseX, int mouseY, bool showInventory);
	void Draw(SDL_Renderer* renderer, SDL_Texture* sprites);

	int GetHoveredX() const;
	int GetHoveredY() const;
	int GetTileSelectedX() const;
	int GetTileSelectedY() const;
};
