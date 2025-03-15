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

	float count;
} Player;

Player* Player_Create();

void Player_Update(Player* player,
	Uint8* keyboard,
	Box** collisions,
	int collisionsCursor,
	float elapsed);

Box* Player_IsColliding(Player* player, Box** collisions, int collisionsCursor);

void Player_ProcessCollisionsX(Player* player, Box** collisions, int collisionsCursor);
void Player_ProcessCollisionsY(Player* player, Box** collisions, int collisionsCursor);

void Player_Free(Player* player);
