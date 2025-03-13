#pragma once

#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Position.h"

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Position pointed,
    Position selected);

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Position** frontTiles,
    Position pointed,
    bool isTileSelected);

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Position pointed,
    Position selected,
    int mode,
    int grid,
    bool isTileSelected);
