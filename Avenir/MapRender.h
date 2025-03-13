#pragma once

#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Map.h"

void MapRender_Draw(Map* map, SDL_Renderer* renderer, SDL_Texture* sprites, bool behind, float playerY);
