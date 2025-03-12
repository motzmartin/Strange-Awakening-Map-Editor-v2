#pragma once

#include <SDL3/SDL.h>

class Player
{
private:
	int x = 0;
	int y = 0;

public:
	void Update(Uint8* keyboard);
	void Draw(SDL_Renderer* renderer);

	int GetY() const;
};
