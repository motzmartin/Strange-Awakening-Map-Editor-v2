#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "GameObjects.h"
#include "DynamicArray.h"
#include "Vector.h"
#include "VectorF.h"

typedef struct Player
{
	VectorF pos;
	VectorF acc;

	Vector sprite;

	float counter;
} Player;

Player* Player_Create();

void Player_Update(Player* player, Uint8* keyboard, DynamicArray* collisions, float elapsed);

Box* Player_IsColliding(Player* player, DynamicArray* collisions);

void Player_ProcessCollisionsX(Player* player, DynamicArray* collisions);
void Player_ProcessCollisionsY(Player* player, DynamicArray* collisions);

void Player_Free(Player* player);
