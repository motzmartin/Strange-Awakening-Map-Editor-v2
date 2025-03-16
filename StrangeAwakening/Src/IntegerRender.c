#include "IntegerRender.h"

void IntegerRender_FillRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)
{
    SDL_FRect fRect = { 0 };
    SDL_RectToFRect(&rect, &fRect);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &fRect);
}

void IntegerRender_DrawTexture(SDL_Renderer* renderer,
    SDL_Texture* texture,
    SDL_Rect srcRect,
    SDL_Rect dstRect)
{
    SDL_FRect fSrcRect = { 0 };
    SDL_RectToFRect(&srcRect, &fSrcRect);

    SDL_FRect fDstRect = { 0 };
    SDL_RectToFRect(&dstRect, &fDstRect);

    SDL_RenderTexture(renderer, texture, &fSrcRect, &fDstRect);
}
