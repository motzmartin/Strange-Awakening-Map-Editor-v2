#pragma once

#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Map.h"

#include "DynamicArray.h"
#include "Vector.h"
#include "IntegerRender.h"

void MapRender_Draw(Map* map,
    SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    float playerY,
    bool behind);
