#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "VectorF.h"

#include "Tile.h"
#include "Box.h"

void LevelLoader_Save(VectorF spawnPoint,
	Tile** tiles,
	Box** collisions,
	Box** rooms,
	int tilesCursor,
	int collisionsCursor,
	int roomsCursor);

void LevelLoader_Load(VectorF* spawnPoint,
	Tile** oldTiles,
	Box** oldCollisions,
	Box** oldRooms,
	int* oldTilesCursor,
	int* oldCollisionsCursor,
	int* oldRoomsCursor);
