#pragma once

#include <math.h>
#include <SDL3/SDL.h>

#include "Player.h"

#include "IntegerRender.h"
#include "Vector.h"
#include "VectorConversion.h"

void PlayerRender_Draw(Player* player,
	SDL_Renderer* renderer,
	SDL_Texture* sprite,
	Vector cameraCentered);
