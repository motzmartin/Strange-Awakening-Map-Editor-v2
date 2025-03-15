#pragma once

#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "IntegerRender.h"

#include "Map.h"

void MapRender_Draw(Map* map,
    SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    float playerY,
    bool behind);

void MapRender_DrawLights(Map* map, SDL_Renderer* renderer, Vector cameraCentered);
