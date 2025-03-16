#pragma once

#include <SDL3/SDL.h>

void IntegerRender_FillRect(SDL_Renderer* renderer,
    SDL_Rect rect,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a);

void IntegerRender_DrawTexture(SDL_Renderer* renderer,
    SDL_Texture* texture,
    SDL_Rect srcRect,
    SDL_Rect dstRect);
