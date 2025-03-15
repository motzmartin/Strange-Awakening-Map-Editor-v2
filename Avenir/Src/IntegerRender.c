#include "IntegerRender.h"

void IntegerRender_FillRect(SDL_Renderer* renderer,
    SDL_Rect rect,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a)
{
    SDL_FRect fRect = { 0 };
    SDL_RectToFRect(&rect, &fRect);

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &fRect);
}

void IntegerRender_DrawSprite(SDL_Renderer* renderer,
    SDL_Texture* sprite,
    SDL_Rect srcRect,
    SDL_Rect dstRect)
{
    SDL_FRect fSrcRect = { 0 };
    SDL_RectToFRect(&srcRect, &fSrcRect);

    SDL_FRect fDstRect = { 0 };
    SDL_RectToFRect(&dstRect, &fDstRect);

    SDL_RenderTexture(renderer, sprite, &fSrcRect, &fDstRect);
}
