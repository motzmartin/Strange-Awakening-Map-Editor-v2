#include "HudRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected,
    Vector cameraPos,
    int mode,
    bool grid,
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
            Vector selectedPos = { cursor.x - cameraPos.x, cursor.y - cameraPos.y };
            if (mode == 2)
            {
                HudRender_DrawRect(renderer, selectedPos, 48.f, 255, 255, 255);
            }
            else if (mode == 3)
            {
                HudRender_DrawRect(renderer, selectedPos, 48.f, 255, 0, 0);
            }
        }
    }
    else
    {
        Vector tilePos = { cursor.x - cameraPos.x, cursor.y - cameraPos.y };

        SDL_FRect tileSrc = { selected.x / 3.f, selected.y / 3.f, 16.f, 16.f };
        SDL_FRect tileDst = { tilePos.x, tilePos.y, 48.f, 48.f };
        SDL_RenderTexture(renderer, sprites, &tileSrc, &tileDst);

        if (grid)
        {
            HudRender_DrawGrid(renderer, cameraPos);
        }
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
    HudRender_DrawRect(renderer, cursorPos, 48.f, 255, 255, 255);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = { selected.x + 384.f, selected.y + 192.f };
        HudRender_DrawRect(renderer, selectedPos, 48.f, 0, 255, 0);
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
            Vector frontPos = { tilePos.x - cameraPos.x, tilePos.y - cameraPos.y };
            HudRender_DrawRect(renderer, frontPos, 48.f, 255, 255, 0);
        }
    }
}

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraPos)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 24 + 1; i++)
    {
        SDL_FRect rect = { (float)i * 48.f - fmodf(cameraPos.x, 48.f), 0.f, 3.f, 768.f };
        SDL_RenderFillRect(renderer, &rect);
    }

    for (int i = 0; i < 16 + 1; i++)
    {
        SDL_FRect rect = { 0.f, (float)i * 48.f - fmodf(cameraPos.y, 48.f), 1152.f, 3.f };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector position,
    float size,
    Uint8 r,
    Uint8 g,
    Uint8 b)
{
    SDL_FRect leftSide = { position.x, position.y, 3.f, size };
    SDL_FRect rightSide = { position.x + size - 3.f, position.y, 3.f, size };
    SDL_FRect topSide = { position.x + 3.f, position.y, size - 6.f, 3.f };
    SDL_FRect bottomSide = { position.x + 3.f, position.y + size - 3.f, size - 6.f, 3.f };

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &leftSide);
    SDL_RenderFillRect(renderer, &rightSide);
    SDL_RenderFillRect(renderer, &topSide);
    SDL_RenderFillRect(renderer, &bottomSide);
}
