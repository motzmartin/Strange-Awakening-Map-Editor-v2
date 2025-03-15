#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Vector.h"

#include "Tile.h"
#include "Box.h"
#include "Light.h"

typedef struct Map
{
	int size;

	Tile** tiles;
	Box** collisions;
	Box** rooms;
	Light** lights;

	int tilesCursor;
	int collisionsCursor;
	int roomsCursor;
	int lightsCursor;

	SDL_Texture* lightsTexture;

	Vector lightsPos;
	Vector lightsSize;
} Map;

Map* Map_Create(int size);

void* Map_ArrayAdd(Map* map, void** arr, int* cursor, size_t size);

void Map_AddTile(Map* map, Vector position, Vector selected, bool front);
void Map_AddCollision(Map* map, Vector position, Vector size);
void Map_AddRoom(Map* map, Vector position, Vector size);
void Map_AddLight(Map* map, Vector position, Vector size, bool emit);

void Map_ArrayRemove(void** arr, int* cursor, int index);

void Map_RemoveTile(Map* map, int index);
void Map_RemoveCollision(Map* map, int index);
void Map_RemoveRoom(Map* map, int index);
void Map_RemoveLight(Map* map, int index);

int Map_GetTileIndex(Map* map, Vector position);
int Map_GetCollisionIndex(Map* map, Vector position);
int Map_GetRoomIndex(Map* map, Vector position);
int Map_GetLightIndex(Map* map, Vector position);

void Map_SwitchFrontTile(Map* map, int index);

void Map_Free(Map* map);

void Map_ProcessLights(Map* map, SDL_Renderer* renderer);
