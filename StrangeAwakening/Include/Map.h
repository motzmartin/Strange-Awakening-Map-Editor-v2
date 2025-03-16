#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "GameObjects.h"

#include "DynamicArray.h"
#include "Vector.h"

typedef struct Map
{
	int size;

	DynamicArray* tiles;
	DynamicArray* boxes[SIZE];
} Map;

Map* Map_Create(int size);

void Map_AddTile(Map* map, Vector pos, Vector selected, bool front);
void Map_AddBox(Map* map, BoxType type, Vector pos, Vector size);

void Map_RemoveTile(Map* map, int index);
void Map_RemoveBox(Map* map, BoxType type, int index);

int Map_GetTileIndexByPos(Map* map, Vector pos);
int Map_GetBoxIndexByPos(Map* map, BoxType type, Vector pos);

void Map_SwitchFrontTile(Map* map, int index);

void Map_Free(Map* map);
