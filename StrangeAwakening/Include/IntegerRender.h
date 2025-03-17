#pragma once

#include <SDL3/SDL.h>

#include "Vector.h"

void IntegerRender_FillRect(SDL_Renderer* renderer,
    Vector pos,
    Vector size,
    SDL_Color color);

void IntegerRender_DrawTexture(SDL_Renderer* renderer,
    SDL_Texture* texture,
    Vector srcPos,
    Vector srcSize,
    Vector destPos,
    Vector destSize);

void IntegerRender_DrawSelection(SDL_Renderer* renderer,
    Vector pos,
    int size,
    SDL_Color color);
