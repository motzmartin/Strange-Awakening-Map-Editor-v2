#pragma once

#include <SDL3/SDL.h>

void IntegerRender_FillRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

void IntegerRender_DrawTexture(SDL_Renderer* renderer,
    SDL_Texture* texture,
    SDL_Rect srcRect,
    SDL_Rect dstRect);
