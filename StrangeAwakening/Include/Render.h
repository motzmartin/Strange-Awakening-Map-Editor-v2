#pragma once

#include <SDL3/SDL.h>

#include "Vector.h"

void Render_FillRect(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color);

void Render_DrawSelection(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color);

void Render_DrawRect(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color);

void Render_DrawTexture(SDL_Renderer* renderer,
    SDL_Texture* texture,
    Vector srcPos,
    Vector srcSize,
    Vector destPos,
    Vector destSize);
