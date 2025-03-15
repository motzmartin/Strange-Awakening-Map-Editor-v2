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
	Box** collisions;
	Box** rooms;

	int tilesCursor;
	int collisionsCursor;
	int roomsCursor;
} Map;

Map* Map_Create(int size);

void* Map_ArrayAdd(Map* map, void** arr, int* cursor, size_t size);

void Map_AddTile(Map* map, Vector position, Vector selected, bool front);
void Map_AddCollision(Map* map, Vector position, Vector size);
void Map_AddRoom(Map* map, Vector position, Vector size);

void Map_ArrayRemove(void** arr, int* cursor, int index);

void Map_RemoveTile(Map* map, int index);
void Map_RemoveCollision(Map* map, int index);
void Map_RemoveRoom(Map* map, int index);

int Map_GetTileIndex(Map* map, Vector position);
int Map_GetCollisionIndex(Map* map, Vector position);
int Map_GetRoomIndex(Map* map, Vector position);

void Map_SwitchFrontTile(Map* map, int index);

void Map_Free(Map* map);
