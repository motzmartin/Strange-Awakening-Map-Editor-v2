#pragma once

#include <stdlib.h>
#include <SDL3/SDL.h>

#include "Vector.h"

typedef struct Player
{
	Vector pos;
	Vector sprite;

	Uint64 count;
} Player;

Player* Player_Create();

void Player_Update(Player* player, Uint8* keyboard, Uint64 elapsed);

void Player_Free(Player* player);
