#pragma once

#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "IntegerRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected,
    Vector cameraCentered,
    int mode,
    bool grid,
    bool isTileSelected);

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected);

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cursor,
    Vector cameraCentered,
    Vector* frontTiles,
    int frontTilesNumber,
    bool isTileSelected);

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered);

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector position,
    int size,
    Uint8 r,
    Uint8 g,
    Uint8 b);
