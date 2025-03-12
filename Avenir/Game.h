#pragma once

#include <memory>
#include <cmath>
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

	SDL_FPoint pointed = { 0 };
	SDL_FPoint selected = { 0 };

	int tileSelected = -1;
	int grid = 0;
	int mode = 0;

	void SetPointed(SDL_FPoint mouse);

public:
	Game();

	void Update(bool* events, SDL_FPoint mouse, Uint8* keyboard);
	void Draw(SDL_Renderer* renderer, SDL_Texture** textures);
};
