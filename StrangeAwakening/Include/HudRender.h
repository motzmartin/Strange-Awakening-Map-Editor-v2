#pragma once

#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "GameObjects.h"

#include "DynamicArray.h"
#include "IntegerRender.h"
#include "Vector.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    SDL_Texture* ui,
    Vector cameraCentered,
    Vector cursor,
    Vector selected,
    DynamicArray* tiles,
    DynamicArray** boxes,
    Vector size,
    int pointed,
    int mode,
    int modeSelected,
    bool showInventory,
    bool grid);

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected);

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray* tiles,
    int pointed);

void HudRender_DrawBoxes(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray* boxes,
    int pointed,
    SDL_Color baseColor);

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered);

void HudRender_DrawRect(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color);
