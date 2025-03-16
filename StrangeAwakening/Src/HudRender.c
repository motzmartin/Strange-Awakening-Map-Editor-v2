#include "HudRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    Vector cursor,
    Vector selected,
    DynamicArray* tiles,
    DynamicArray** boxes,
    Vector* sizes,
    int pointed,
    int mode,
    bool grid)
{
    if (mode == 1)
    {
        HudRender_DrawInventory(renderer, sprites, cursor, selected);
    }
    else
    {
        if (grid)
        {
            HudRender_DrawGrid(renderer, cameraCentered);
        }

        if (mode == 2 || mode == 3)
        {
            if (pointed != -1)
            {
                Tile* tile = DynamicArray_Get(tiles, pointed);

                Vector tilePos = { tile->pos.x * 12 - cameraCentered.x, tile->pos.y * 12 - cameraCentered.y };

                Uint8 r = 255;
                Uint8 g = 255;
                Uint8 b = 255;

                if (mode == 3)
                {
                    g = 0;
                    b = 0;
                }

                HudRender_DrawRect(renderer, tilePos, Vector_New(48, 48), r, g, b, 255);
            }

            if (mode == 2)
            {
                HudRender_DrawFrontTiles(renderer, cameraCentered, tiles, pointed);
            }
        }
        else if (mode >= 4 && mode <= 7)
        {
            Vector cursorPos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };

            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0;

            BoxType type = mode - 4;

            if (type == COLLISIONS) b = 255;
            else if (type == ROOMS) r = b = 255;
            else if (type == LIGHTS) g = b = 255;
            else if (type == EMIT_LIGHTS) r = g = 255;

            if (pointed == -1)
            {
                HudRender_DrawRect(renderer, cursorPos, Vector_Scale(sizes[type], 12), r, g, b, 255);
            }

            HudRender_DrawBoxes(renderer, cameraCentered, boxes[type], pointed, r, g, b);
        }
        else
        {
            Vector cursorPos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };

            SDL_Rect tileSrc = { selected.x * 16, selected.y * 16, 16, 16 };
            SDL_Rect tileDst = { cursorPos.x, cursorPos.y, 48, 48 };
            IntegerRender_DrawTexture(renderer, sprites, tileSrc, tileDst);
        }
    }
}

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected)
{
    SDL_Rect backgroundRect = { 0, 0, 1152, 768 };
    IntegerRender_FillRect(renderer, backgroundRect, 63, 63, 63, 255);

    SDL_Rect inventorySrc = { 0, 0, 128, 128 };
    SDL_Rect inventoryDst = { 384, 192, 384, 384 };
    IntegerRender_DrawTexture(renderer, sprites, inventorySrc, inventoryDst);

    Vector cursorPos = { (cursor.x + 8) * 48, (cursor.y + 4) * 48 };
    HudRender_DrawRect(renderer, cursorPos, Vector_New(48, 48), 255, 255, 255, 255);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = { (selected.x + 8) * 48, (selected.y + 4) * 48 };
        HudRender_DrawRect(renderer, selectedPos, Vector_New(48, 48), 0, 255, 0, 255);
    }
}

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray* tiles,
    int pointed)
{
    for (int i = 0; i < DynamicArray_GetSize(tiles); i++)
    {
        Tile* tile = DynamicArray_Get(tiles, i);

        if (tile->front && i != pointed)
        {
            Vector pos = { tile->pos.x * 12 - cameraCentered.x, tile->pos.y * 12 - cameraCentered.y };
            HudRender_DrawRect(renderer, pos, Vector_New(48, 48), 255, 255, 0, 255);
        }
    }
}

void HudRender_DrawBoxes(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray* boxes,
    int pointed,
    Uint8 baseR,
    Uint8 baseG,
    Uint8 baseB)
{
    for (int i = 0; i < DynamicArray_GetSize(boxes); i++)
    {
        Box* box = DynamicArray_Get(boxes, i);

        Uint8 r = baseR;
        Uint8 g = baseG;
        Uint8 b = baseB;

        if (i == pointed)
        {
            r = 255;
            g = b = 0;
        }

        Vector pos = { box->pos.x * 12 - cameraCentered.x, box->pos.y * 12 - cameraCentered.y };
        HudRender_DrawRect(renderer, pos, Vector_Scale(box->size, 12), r, g, b, 255);
    }
}

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered)
{
    for (int i = 0; i < 24 + 1; i++)
    {
        int mod = HudRender_TrueMod(cameraCentered.x, 48);

        SDL_Rect rect = { i * 48 - mod, 0, 3, 768 };

        Uint8 r = 255;
        Uint8 g = 255;
        Uint8 b = 255;
        Uint8 a = 63;

        if (rect.x + cameraCentered.x == 0)
        {
            r = b = 0;
            a = 127;
        }

        IntegerRender_FillRect(renderer, rect, r, g, b, a);
    }

    for (int i = 0; i < 16 + 1; i++)
    {
        int mod = HudRender_TrueMod(cameraCentered.y, 48);

        SDL_Rect rect = { 0, i * 48 - mod, 1152, 3 };

        Uint8 r = 255;
        Uint8 g = 255;
        Uint8 b = 255;
        Uint8 a = 63;

        if (rect.y + cameraCentered.y == 0)
        {
            g = b = 0;
            a = 127;
        }

        IntegerRender_FillRect(renderer, rect, r, g, b, a);
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector pos,
    Vector size,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a)
{
    SDL_Rect leftSide = { pos.x, pos.y, 3, size.y };
    SDL_Rect rightSide = { pos.x + size.x - 3, pos.y, 3, size.y };

    SDL_Rect topSide = { pos.x + 3, pos.y, size.x - 6, 3 };
    SDL_Rect bottomSide = { pos.x + 3, pos.y + size.y - 3, size.x - 6, 3 };

    IntegerRender_FillRect(renderer, leftSide, r, g, b, a);
    IntegerRender_FillRect(renderer, rightSide, r, g, b, a);
    IntegerRender_FillRect(renderer, topSide, r, g, b, a);
    IntegerRender_FillRect(renderer, bottomSide, r, g, b, a);
}

int HudRender_TrueMod(int a, int b)
{
    int r = a % b;

    return (r < 0) ? r + abs(b) : r;
}
