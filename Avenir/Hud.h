#pragma once

#include <SDL3/SDL.h>

class Hud
{
private:
	int selectedX = 0;
	int selectedY = 0;

	bool enabled = true;

public:
	void Update(int mouseX, int mouseY, bool trigger);
	void Draw(SDL_Renderer* renderer,
		int mouseX,
		int mouseY,
		SDL_Texture* cursor,
		SDL_Texture* grid,
		SDL_Texture* selection);

	int GetSelectedX() const;
	int GetSelectedY() const;
	bool IsEnabled() const;
};
