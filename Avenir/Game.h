#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Position.h"

#include "Hud.h"
#include "Map.h"
#include "Player.h"

#include "HudRender.h"
#include "MapRender.h"
#include "PlayerRender.h"

typedef struct Game
{
	Map* map;
	Player* player;

	Position pointed;
	Position selected;

	int tileSelected;
	int grid;
	int mode;
} Game;

Game* Game_Create();

void Game_SetPointed(Game* game, Position mouse);

void Game_Update(Game* game, bool* events, Position mouse, Uint8* keyboard);
void Game_Draw(Game* game, SDL_Renderer* renderer, SDL_Texture** textures);

void Game_Free(Game* game);
