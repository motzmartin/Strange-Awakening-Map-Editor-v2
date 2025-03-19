#pragma once

#include <stdbool.h>
#include <SDL3/SDL.h>

#include "GameObjects.h"

#include "DynamicArray.h"
#include "Render.h"
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
    int optionPointed,
    int mode,
    bool showInventory,
    bool grid);

void HudRender_DrawTilePlacement(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector screenPos,
    Vector cameraCentered,
    Vector selected,
    Vector size);

void HudRender_DrawBoxes(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray** boxes,
    Vector screenPos,
    Vector size,
    int pointed,
    int optionPointed,
    int mode);

void HudRender_DrawInventory(SDL_Renderer* renderer, SDL_Texture* sprites, Vector cursor, Vector selected);

void HudRender_DrawOptions(SDL_Renderer* renderer, SDL_Texture* ui, int optionPointed, int mode, bool grid);

void HudRender_DrawRemoveRect(SDL_Renderer* renderer, Vector cameraCentered, DynamicArray* tiles, int pointed);

void HudRender_DrawFrontTiles(SDL_Renderer* renderer, Vector cameraCentered, DynamicArray* tiles, int pointed);

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered);

SDL_Color HudRender_GetBoxColor(BoxType type);
