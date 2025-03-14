#pragma once

#include <stdbool.h>
#include <math.h>
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
