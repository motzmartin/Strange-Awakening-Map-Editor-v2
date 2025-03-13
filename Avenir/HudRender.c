#include "HudRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected,
    Vector cameraPos,
    int mode,
    bool isTileSelected)
{
    if (mode == 1)
    {
        SDL_SetTextureAlphaMod(sprites, 255);

        HudRender_DrawInventory(renderer, sprites, cursor, selected);
    }
    else if (mode == 2 || mode == 3)
    {
        if (isTileSelected)
        {
            Vector selectedPos = { floorf(cursor.x - cameraPos.x), floorf(cursor.y - cameraPos.y) };
            if (mode == 2)
            {
                HudRender_DrawRect(renderer, selectedPos, 255, 255, 255);
            }
            else if (mode == 3)
            {
                HudRender_DrawRect(renderer, selectedPos, 255, 0, 0);
            }
        }
    }
    else
    {
        SDL_SetTextureAlphaMod(sprites, 191);

        SDL_FRect tileSrc = { selected.x / 3.f, selected.y / 3.f, 16.f, 16.f };
        SDL_FRect tileDst =
        {
            floorf(cursor.x - cameraPos.x),
            floorf(cursor.y - cameraPos.y),
            48.f,
            48.f
        };
        SDL_RenderTexture(renderer, sprites, &tileSrc, &tileDst);
    }
}

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected)
{
    SDL_FRect backgroundRect = { 0.f, 0.f, 1152.f, 768.f };
    SDL_SetRenderDrawColor(renderer, 63, 63, 63, 255);
    SDL_RenderFillRect(renderer, &backgroundRect);

    SDL_FRect inventoryRect = { 384.f, 192.f, 384.f, 384.f };
    SDL_RenderTexture(renderer, sprites, NULL, &inventoryRect);

    Vector cursorPos = { cursor.x + 384.f, cursor.y + 192.f };
    HudRender_DrawRect(renderer, cursorPos, 255, 255, 255);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = { selected.x + 384.f, selected.y + 192.f };
        HudRender_DrawRect(renderer, selectedPos, 0, 255, 0);
    }
}

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cursor,
    Vector cameraPos,
    Vector* frontTiles,
    int frontTilesNumber,
    bool isTileSelected)
{
    for (int i = 0; i < frontTilesNumber; i++)
    {
        Vector tilePos = frontTiles[i];

        if (!isTileSelected || (cursor.x != tilePos.x || cursor.y != tilePos.y))
        {
            Vector frontPos = { floorf(tilePos.x - cameraPos.x), floorf(tilePos.y - cameraPos.y) };
            HudRender_DrawRect(renderer, frontPos, 255, 255, 0);
        }
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector position,
    Uint8 r,
    Uint8 g,
    Uint8 b)
{
    SDL_FRect leftSide = { position.x, position.y, 3.f, 48.f };
    SDL_FRect rightSide = { position.x + 45.f, position.y, 3.f, 48.f };
    SDL_FRect topSide = { position.x + 3.f, position.y, 43.f, 3.f };
    SDL_FRect bottomSide = { position.x + 3.f, position.y + 45.f, 43.f, 3.f };

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &leftSide);
    SDL_RenderFillRect(renderer, &rightSide);
    SDL_RenderFillRect(renderer, &topSide);
    SDL_RenderFillRect(renderer, &bottomSide);
}
