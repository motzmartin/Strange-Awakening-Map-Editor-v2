#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Position.h"

typedef struct Tile
{
	Position pos;
	Position sprite;

	bool front;
} Tile;

typedef struct Map
{
	Tile** tiles;
} Map;

Map* Map_Create();

void Map_AddTile(Map* map, Position position, Position sprite, bool front);
void Map_RemoveTile(Map* map, int index);
void Map_SwitchFrontTile(Map* map, int index);

int Map_GetTile(Map* map, Position pos, Position* tilePos);
Position** Map_GetFrontTiles(Map* map);
void Map_FreeFrontTiles(Position** frontTiles);

void Map_Free(Map* map);
