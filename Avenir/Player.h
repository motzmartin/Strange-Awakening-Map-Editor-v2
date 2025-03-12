#pragma once

#include <SDL3/SDL.h>

class Player
{
private:
	SDL_FPoint pos = { 0 };

public:
	void Update(Uint8* keyboard);
	void Draw(SDL_Renderer* renderer);

	float GetY() const;
};
