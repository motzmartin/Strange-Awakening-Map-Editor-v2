#pragma once

#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "IntegerRender.h"

#include "Tile.h"
#include "Box.h"
#include "Light.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    Vector cursor,
    Vector selected,
    Vector collisionSize,
    Vector roomSize,
    Vector lightSize,
    Tile** tiles,
    Box** collisions,
    Box** rooms,
    Light** lights,
    int tilesCursor,
    int collisionsCursor,
    int roomsCursor,
    int lightsCursor,
    int tilePointed,
    int collisionPointed,
    int roomPointed,
    int lightPointed,
    int mode,
    bool grid);

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected);

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cameraCentered,
    Tile** tiles,
    int tilesCursor,
    int tilePointed);

void HudRender_DrawCollisions(SDL_Renderer* renderer,
    Vector cameraCentered,
    Box** collisions,
    int collisionsCursor,
    int collisionPointed);

void HudRender_DrawRooms(SDL_Renderer* renderer,
    Vector cameraCentered,
    Box** rooms,
    int roomsCursor,
    int roomPointed);

void HudRender_DrawLights(SDL_Renderer* renderer,
    Vector cameraCentered,
    Light** lights,
    int lightsCursor,
    int lightPointed);

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered);

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector position,
    Vector size,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a);

int HudRender_TrueMod(int a, int b);
