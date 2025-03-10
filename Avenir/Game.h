#pragma once

#include <SDL3/SDL.h>

#include "Hud.h"
#include "Grid.h"

class Game
{
private:
	Hud hud;
	Grid grid;

public:
	void Update(bool* events, Uint8* keyboard, int mouseX, int mouseY);

	Hud* GetHud();
	Grid* GetGrid();
};
