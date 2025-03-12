#pragma once

#include <memory>
#include <SDL3/SDL.h>

#include "Hud.h"
#include "Map.h"
#include "Player.h"

class Game
{
private:
	std::unique_ptr<Hud> hud;
	std::unique_ptr<Map> map;
	std::unique_ptr<Player> player;

	int pointedX = 0;
	int pointedY = 0;

	int selectedX = 0;
	int selectedY = 0;

	int tileSelected = -1;

	int menu = 0;

	void SetPointed(int mouseX, int mouseY);

public:
	Game();

	void Update(bool* events, int mouseX, int mouseY, Uint8* keyboard);
	void Draw(SDL_Renderer* renderer, SDL_Texture** textures);
};
