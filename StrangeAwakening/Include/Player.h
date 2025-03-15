#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "VectorF.h"

#include "Box.h"

typedef struct Player
{
	VectorF pos;
	VectorF acc;

	Vector sprite;

	Uint64 count;
} Player;

Player* Player_Create();

void Player_Update(Player* player,
	Uint64 elapsed,
	Uint8* keyboard,
	Box** collisions,
	int collisionsCursor);

Box* Player_IsColliding(Player* player, Box** collisions, int collisionsCursor);

void Player_ProcessCollisionsX(Player* player, Box** collisions, int collisionsCursor);
void Player_ProcessCollisionsY(Player* player, Box** collisions, int collisionsCursor);

void Player_Free(Player* player);
