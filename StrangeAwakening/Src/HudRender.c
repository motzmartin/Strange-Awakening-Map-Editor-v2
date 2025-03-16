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
                Vector screenPos = { tile->pos.x * 12 - cameraCentered.x, tile->pos.y * 12 - cameraCentered.y };

                SDL_Color color = { 255, 255, 255, 255 };
                if (mode == 3) color.g = color.b = 0;

                HudRender_DrawRect(renderer, screenPos, Vector_New(48, 48), color);
            }

            if (mode == 2)
            {
                HudRender_DrawFrontTiles(renderer, cameraCentered, tiles, pointed);
            }
        }
        else
        {
            Vector screenPos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };

            if (mode >= 4 && mode <= 7)
            {
                BoxType type = mode - 4;

                SDL_Color color = { 0, 0, 0, 255 };
                if (type == COLLISIONS) color.b = 255;
                else if (type == ROOMS) color.r = color.b = 255;
                else if (type == LIGHTS) color.g = color.b = 255;
                else if (type == EMIT_LIGHTS) color.r = color.g = 255;

                if (pointed == -1)
                {
                    HudRender_DrawRect(renderer, screenPos, Vector_Scale(sizes[type], 12), color);
                }

                HudRender_DrawBoxes(renderer, cameraCentered, boxes[type], pointed, color);
            }
            else
            {
                SDL_Rect tileSrc = { selected.x * 16, selected.y * 16, 16, 16 };
                SDL_Rect tileDst = { screenPos.x, screenPos.y, 48, 48 };
                IntegerRender_DrawTexture(renderer, sprites, tileSrc, tileDst);
            }
        }
    }
}

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected)
{
    SDL_Rect backgroundRect = { 0, 0, 1152, 768 };
    SDL_Color backgroundColor = { 63, 63, 63, 255 };
    IntegerRender_FillRect(renderer, backgroundRect, backgroundColor);

    SDL_Rect inventorySrc = { 0, 0, 128, 128 };
    SDL_Rect inventoryDst = { 384, 192, 384, 384 };
    IntegerRender_DrawTexture(renderer, sprites, inventorySrc, inventoryDst);

    Vector cursorPos = { (cursor.x + 8) * 48, (cursor.y + 4) * 48 };
    SDL_Color cursorColor = { 255, 255, 255, 255 };
    HudRender_DrawRect(renderer, cursorPos, Vector_New(48, 48), cursorColor);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = { (selected.x + 8) * 48, (selected.y + 4) * 48 };
        SDL_Color selectedColor = { 0, 255, 0, 255 };
        HudRender_DrawRect(renderer, selectedPos, Vector_New(48, 48), selectedColor);
    }
}

void HudRender_DrawFrontTiles(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray* tiles,
    int pointed)
{
    SDL_Color color = { 255, 255, 0, 255 };

    for (int i = 0; i < DynamicArray_GetSize(tiles); i++)
    {
        Tile* tile = DynamicArray_Get(tiles, i);

        if (tile->front && i != pointed)
        {
            Vector screenPos = { tile->pos.x * 12 - cameraCentered.x, tile->pos.y * 12 - cameraCentered.y };
            HudRender_DrawRect(renderer, screenPos, Vector_New(48, 48), color);
        }
    }
}

void HudRender_DrawBoxes(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray* boxes,
    int pointed,
    SDL_Color baseColor)
{
    for (int i = 0; i < DynamicArray_GetSize(boxes); i++)
    {
        Box* box = DynamicArray_Get(boxes, i);
        Vector screenPos = { box->pos.x * 12 - cameraCentered.x, box->pos.y * 12 - cameraCentered.y };

        SDL_Color color = baseColor;
        if (i == pointed)
        {
            color.r = 255;
            color.g = color.b = 0;
        }

        HudRender_DrawRect(renderer, screenPos, Vector_Scale(box->size, 12), color);
    }
}

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered)
{
    Vector mod = Vector_Mod(cameraCentered, Vector_New(48, 48));

    for (int i = 0; i < 24 + 1; i++)
    {
        SDL_Rect horizontal = { i * 48 - mod.x, 0, 3, 768 };

        SDL_Color color = { 255, 255, 255, 63 };
        if (horizontal.x + cameraCentered.x == 0)
        {
            color.r = color.b = 0;
            color.a = 127;
        }

        IntegerRender_FillRect(renderer, horizontal, color);
    }

    for (int i = 0; i < 16 + 1; i++)
    {
        SDL_Rect vertical = { 0, i * 48 - mod.y, 1152, 3 };

        SDL_Color color = { 255, 255, 255, 63 };
        if (vertical.y + cameraCentered.y == 0)
        {
            color.g = color.b = 0;
            color.a = 127;
        }

        IntegerRender_FillRect(renderer, vertical, color);
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector pos,
    Vector size,
    SDL_Color color)
{
    SDL_Rect leftSide = { pos.x, pos.y, 3, size.y };
    SDL_Rect rightSide = { pos.x + size.x - 3, pos.y, 3, size.y };
    SDL_Rect topSide = { pos.x + 3, pos.y, size.x - 6, 3 };
    SDL_Rect bottomSide = { pos.x + 3, pos.y + size.y - 3, size.x - 6, 3 };

    IntegerRender_FillRect(renderer, leftSide, color);
    IntegerRender_FillRect(renderer, rightSide, color);
    IntegerRender_FillRect(renderer, topSide, color);
    IntegerRender_FillRect(renderer, bottomSide, color);
}
