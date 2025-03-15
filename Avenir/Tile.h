#pragma once

#include <stdbool.h>

#include "Vector.h"

typedef struct Tile
{
	Vector pos;
	Vector sprite;

	bool front;
} Tile;
