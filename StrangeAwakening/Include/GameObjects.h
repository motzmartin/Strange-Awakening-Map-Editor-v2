#pragma once

#include <stdbool.h>

#include "Vector.h"

typedef enum BoxType
{
	COLLISIONS,
	ROOMS,
	LIGHTS,
	EMIT_LIGHTS,
	SIZE
} BoxType;

typedef struct Box
{
	Vector pos;
	Vector size;
} Box;

typedef struct Tile
{
	Vector pos;
	Vector sprite;

	bool front;
} Tile;
