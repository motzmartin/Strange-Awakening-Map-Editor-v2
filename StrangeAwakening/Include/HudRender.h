#pragma once

#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "GameObjects.h"

#include "DynamicArray.h"
#include "Vector.h"
#include "IntegerRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    Vector cursor,
    Vector selected,
    DynamicArray* tiles,
    DynamicArray** boxes,
    Vector* sizes,
    int pointed,
    int mode,
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
    Uint8 baseR,
    Uint8 baseG,
    Uint8 baseB);

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered);

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector pos,
    Vector size,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a);
