#pragma once

#include <memory>
#include <SDL3/SDL.h>

#include "Hud.h"
#include "Map.h"

class Game
{
private:
	std::unique_ptr<Hud> hud;
	std::unique_ptr<Map> map;

public:
	Game();

	void Update(bool* events, int mouseX, int mouseY, Uint8* keyboard);
	void Draw(SDL_Renderer* renderer, SDL_Texture** textures);
};
