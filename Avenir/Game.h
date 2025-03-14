#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Vector.h"

#include "Map.h"
#include "Player.h"
#include "Camera.h"

#include "HudRender.h"
#include "MapRender.h"
#include "PlayerRender.h"

typedef struct Game
{
	Map* map;
	Player* player;
	Camera* camera;

	Vector cursor;
	Vector selected;

	int tilePointed;
	int mode;

	bool grid;

	Uint64 timer;
} Game;

Game* Game_Create();

void Game_UpdateCursor(Game* game, Vector mouse);

void Game_Update(Game* game, bool* events, Vector mouse, Uint8* keyboard);
void Game_Draw(Game* game, SDL_Renderer* renderer, SDL_Texture** textures);

void Game_Free(Game* game);
