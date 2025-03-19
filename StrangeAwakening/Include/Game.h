#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Lights.h"
#include "LevelLoader.h"
#include "TextureLoader.h"

#include "HudRender.h"
#include "MapRender.h"
#include "PlayerRender.h"
#include "LightsRender.h"

#include "GameObjects.h"

#include "Vector.h"

typedef struct Game
{
	Map* map;
	Player* player;
	Camera* camera;
	Lights* lights;

	Vector cursor;
	Vector selected;
	Vector size;

	int pointed;
	int optionPointed;
	int mode;

	bool showInventory;
	bool resizeActive;
	bool grid;

	Uint64 counter;
} Game;

Game* Game_Create();

void Game_Update(Game* game, SDL_Renderer* renderer, bool* events, Vector mouse, Uint8* keyboard);
void Game_UpdateCursor(Game* game, Vector mouse);
void Game_Draw(Game* game, SDL_Renderer* renderer, DynamicArray* textures);

int Game_GetOptionPointed(Game* game, Vector mouse);

void Game_Free(Game* game);
