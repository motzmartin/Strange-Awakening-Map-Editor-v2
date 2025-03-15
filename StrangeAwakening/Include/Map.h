#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Vector.h"

#include "Tile.h"
#include "Box.h"

typedef struct Map
{
	int size;

	Tile** tiles;
	int tilesCursor;

	Box** collisions;
	int collisionsCursor;
} Map;

Map* Map_Create(int size);

void Map_AddTile(Map* map, Vector position, Vector selected, bool front);
void Map_RemoveTile(Map* map, int index);

void Map_AddCollision(Map* map, Vector position, Vector size);
void Map_RemoveCollision(Map* map, int index);

int Map_GetTileIndex(Map* map, Vector position);
Vector Map_GetTilePosition(Map* map, int index);

int Map_GetCollisionIndex(Map* map, Vector position);
Vector Map_GetCollisionPosition(Map* map, int index);

void Map_SwitchFrontTile(Map* map, int index);

void Map_Free(Map* map);
