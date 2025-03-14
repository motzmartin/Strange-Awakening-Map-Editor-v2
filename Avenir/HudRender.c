#include "HudRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected,
    Vector cameraCentered,
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
            Vector selectedPos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };
            if (mode == 2)
            {
                HudRender_DrawRect(renderer, selectedPos, 48, 255, 255, 255);
            }
            else if (mode == 3)
            {
                HudRender_DrawRect(renderer, selectedPos, 48, 255, 0, 0);
            }
        }
    }
    else
    {
        Vector tilePos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };

        SDL_Rect tileSrc = { selected.x * 16, selected.y * 16, 16, 16 };
        SDL_Rect tileDst = { tilePos.x, tilePos.y, 48, 48 };
        IntegerRender_DrawSprite(renderer, sprites, tileSrc, tileDst);

        if (grid)
        {
            HudRender_DrawGrid(renderer, cameraCentered);
        }
    }
}

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected)
{
    SDL_Rect backgroundRect = { 0, 0, 1152, 768 };
    IntegerRender_FillRect(renderer, backgroundRect, 63, 63, 63);

    SDL_Rect inventorySrc = { 0, 0, 128, 128 };
    SDL_Rect inventoryDst = { 384, 192, 384, 384 };
    IntegerRender_DrawSprite(renderer, sprites, inventorySrc, inventoryDst);

    Vector cursorPos = { (cursor.x + 8) * 48, (cursor.y + 4) * 48 };
    HudRender_DrawRect(renderer, cursorPos, 48, 255, 255, 255);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = { (selected.x + 8) * 48, (selected.y + 4) * 48 };
        HudRender_DrawRect(renderer, selectedPos, 48, 0, 255, 0);
    }
}

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cursor,
    Vector cameraCentered,
    Vector* frontTiles,
    int frontTilesNumber,
    bool isTileSelected)
{
    for (int i = 0; i < frontTilesNumber; i++)
    {
        Vector tilePos = frontTiles[i];

        if (!isTileSelected || (cursor.x != tilePos.x || cursor.y != tilePos.y))
        {
            Vector frontPos = { tilePos.x * 12 - cameraCentered.x, tilePos.y * 12 - cameraCentered.y };
            HudRender_DrawRect(renderer, frontPos, 48, 255, 255, 0);
        }
    }
}

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered)
{
    for (int i = 0; i < 24 + 1; i++)
    {
        SDL_Rect rect = { i * 48 - cameraCentered.x % 48, 0, 3, 768 };
        IntegerRender_FillRect(renderer, rect, 255, 255, 255);
    }

    for (int i = 0; i < 16 + 1; i++)
    {
        SDL_Rect rect = { 0, i * 48 - cameraCentered.y % 48, 1152, 3 };
        IntegerRender_FillRect(renderer, rect, 255, 255, 255);
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector position,
    int size,
    Uint8 r,
    Uint8 g,
    Uint8 b)
{
    SDL_Rect leftSide = { position.x, position.y, 3, size };
    SDL_Rect rightSide = { position.x + size - 3, position.y, 3, size };
    SDL_Rect topSide = { position.x + 3, position.y, size - 6, 3 };
    SDL_Rect bottomSide = { position.x + 3, position.y + size - 3, size - 6, 3 };

    IntegerRender_FillRect(renderer, leftSide, r, g, b);
    IntegerRender_FillRect(renderer, rightSide, r, g, b);
    IntegerRender_FillRect(renderer, topSide, r, g, b);
    IntegerRender_FillRect(renderer, bottomSide, r, g, b);
}
