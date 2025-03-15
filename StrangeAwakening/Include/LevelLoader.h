#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "VectorF.h"

#include "Tile.h"
#include "Box.h"
#include "Light.h"

void LevelLoader_Save(VectorF spawnPoint,
	Tile** tiles,
	Box** collisions,
	Box** rooms,
	Light** lights,
	int tilesCursor,
	int collisionsCursor,
	int roomsCursor,
	int lightsCursor);

void LevelLoader_Load(VectorF* spawnPoint,
	Tile** oldTiles,
	Box** oldCollisions,
	Box** oldRooms,
	Light** oldLights,
	int* oldTilesCursor,
	int* oldCollisionsCursor,
	int* oldRoomsCursor,
	int* oldLightsCursor);
