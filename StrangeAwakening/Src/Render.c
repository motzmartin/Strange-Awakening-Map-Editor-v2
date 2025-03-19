#include "Render.h"

void Render_FillRect(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color)
{
    SDL_FRect rect = { (float)pos.x, (float)pos.y, (float)size.x, (float)size.y };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Render_DrawRect(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color)
{
    Render_FillRect(renderer, pos, Vector_New(3, size.y), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(size.x - 3, 0)), Vector_New(3, size.y), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(3, 0)), Vector_New(size.x - 6, 3), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(3, size.y - 3)), Vector_New(size.x - 6, 3), color);
}

void Render_DrawSelection(SDL_Renderer* renderer, Vector pos, Vector size, SDL_Color color)
{
    Render_FillRect(renderer, pos, Vector_New(9, 3), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(0, 3)), Vector_New(3, 6), color);

    Render_FillRect(renderer, Vector_Add(pos, Vector_New(size.x - 9, 0)), Vector_New(9, 3), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(size.x - 3, 3)), Vector_New(3, 6), color);

    Render_FillRect(renderer, Vector_Add(pos, Vector_New(0, size.y - 3)), Vector_New(9, 3), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(0, size.y - 9)), Vector_New(3, 6), color);

    Render_FillRect(renderer, Vector_Add(pos, Vector_New(size.x - 9, size.y - 3)), Vector_New(9, 3), color);
    Render_FillRect(renderer, Vector_Add(pos, Vector_New(size.x - 3, size.y - 9)), Vector_New(3, 6), color);
}

void Render_DrawTexture(SDL_Renderer* renderer,
    SDL_Texture* texture,
    Vector srcPos,
    Vector srcSize,
    Vector destPos,
    Vector destSize)
{
    SDL_FRect srcRect = { (float)srcPos.x, (float)srcPos.y, (float)srcSize.x, (float)srcSize.y };
    SDL_FRect dstRect = { (float)destPos.x, (float)destPos.y, (float)destSize.x, (float)destSize.y };

    SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
}
