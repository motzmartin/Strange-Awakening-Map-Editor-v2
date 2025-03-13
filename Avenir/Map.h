#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Vector.h"

typedef struct Tile
{
	Vector pos;
	Vector sprite;

	bool front;
} Tile;

typedef struct Map
{
	Tile** tiles;
	int cursor;
} Map;

Map* Map_Create();

void Map_AddTile(Map* map, Vector position, Vector selected, bool front);
void Map_RemoveTile(Map* map, int index);

int Map_GetTileIndex(Map* map, Vector position);
Vector Map_GetTilePosition(Map* map, int index);

Vector* Map_GetFrontTiles(Map* map, int* frontTilesNumber);
void Map_SwitchFrontTile(Map* map, int index);
void Map_FreeFrontTiles(Vector* frontTiles);

void Map_Free(Map* map);
