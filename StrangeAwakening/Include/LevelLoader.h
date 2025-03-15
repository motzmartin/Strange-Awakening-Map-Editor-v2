#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "VectorF.h"

#include "Tile.h"
#include "Box.h"

void LevelLoader_Save(Tile** tiles,
	Box** collisions,
	Box** rooms,
	int tilesCursor,
	int collisionsCursor,
	int roomsCursor,
	VectorF spawnPoint);

void LevelLoader_Load(Tile** oldTiles,
	Box** oldCollisions,
	Box** oldRooms,
	int* oldTilesCursor,
	int* oldCollisionsCursor,
	int* oldRoomsCursor,
	VectorF* spawnPoint);
