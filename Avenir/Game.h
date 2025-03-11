#pragma once

#include <memory>

#include "Hud.h"
#include "Grid.h"

class Game
{
private:
	std::unique_ptr<Hud> hud;
	std::unique_ptr<Grid> grid;

public:
	Game();

	void Update(bool* events, int mouseX, int mouseY);

	Hud* GetHud();
	Grid* GetGrid();
};
