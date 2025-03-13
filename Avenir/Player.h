#pragma once

#include <stdlib.h>
#include <SDL3/SDL.h>

#include "Position.h"

typedef struct Player
{
	Position pos;
} Player;

Player* Player_Create();

void Player_Update(Player* player, Uint8* keyboard);

void Player_Free(Player* player);
