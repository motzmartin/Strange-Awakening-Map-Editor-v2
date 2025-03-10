#pragma once

#include <SDL3/SDL.h>

class Grid
{
private:
	char** arr = nullptr;

public:
	Grid();
	~Grid();

	void Update(int selectedX, int selectedY, bool mouseDown, bool clear);
	void Draw(SDL_Renderer* renderer);
};
