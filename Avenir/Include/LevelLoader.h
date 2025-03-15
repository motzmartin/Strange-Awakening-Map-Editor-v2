#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "VectorF.h"

#include "Tile.h"
#include "Box.h"

void LevelLoader_Save(Tile** tiles,
	Box** collisions,
	int tilesCursor,
	int collisionsCursor,
	VectorF spawnPoint);

void LevelLoader_Load(Tile** tiles,
	Box** collisions,
	int* oldTilesCursor,
	int* oldCollisionsCursor,
	VectorF* spawnPoint);
