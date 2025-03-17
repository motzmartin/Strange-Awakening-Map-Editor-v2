#include "HudRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    SDL_Texture* ui,
    Vector cameraCentered,
    Vector cursor,
    Vector selected,
    DynamicArray* tiles,
    DynamicArray** boxes,
    Vector size,
    int pointed,
    int mode,
    int modeSelected,
    bool showInventory,
    bool grid)
{
    if (showInventory)
    {
        HudRender_DrawInventory(renderer, sprites, cursor, selected);
    }
    else
    {
        if (grid)
        {
            HudRender_DrawGrid(renderer, cameraCentered);
        }

        if (mode == 1 || mode == 2)
        {
            if (pointed != -1 && modeSelected == -1)
            {
                Tile* tile = DynamicArray_Get(tiles, pointed);
                Vector screenPos = Vector_Sub(Vector_Scale(tile->pos, 12), cameraCentered);

                SDL_Color color = { 255, 255, 255, 255 };
                if (mode == 1) color.g = color.b = 0;

                HudRender_DrawRect(renderer, screenPos, Vector_New(48, 48), color);
            }

            if (mode == 2)
            {
                HudRender_DrawFrontTiles(renderer, cameraCentered, tiles, pointed);
            }
        }
        else
        {
            Vector screenPos = Vector_Sub(Vector_Scale(cursor, 12), cameraCentered);

            if (mode == 0 && modeSelected == -1)
            {
                IntegerRender_DrawTexture(renderer,
                    sprites,
                    Vector_Scale(selected, 16),
                    Vector_New(16, 16),
                    screenPos,
                    Vector_New(48, 48));
            }
            else if (mode >= 3 && mode <= 6)
            {
                BoxType type = mode - 3;

                SDL_Color color = { 0, 0, 0, 255 };
                if (type == COLLISIONS) color.b = 255;
                else if (type == ROOMS) color.r = color.b = 255;
                else if (type == LIGHTS) color.g = color.b = 255;
                else if (type == EMIT_LIGHTS) color.r = color.g = 255;

                if (pointed == -1 && modeSelected == -1)
                {
                    HudRender_DrawRect(renderer, screenPos, Vector_Scale(size, 12), color);
                }

                HudRender_DrawBoxes(renderer, cameraCentered, boxes[type], pointed, color);
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        Vector modePos = Vector_New(i * 30 + 9, 768 - 30 - 3);

        IntegerRender_DrawTexture(renderer, ui, Vector_New(i * 8, 0),Vector_New(8, 8), modePos, Vector_New(24, 24));

        if (i == mode || i == modeSelected)
        {
            SDL_Color color = { 255, 255, 255, 255 };
            HudRender_DrawRect(renderer, Vector_Sub(modePos, Vector_New(3, 3)), Vector_New(30, 30), color);
        }
    }
}

void HudRender_DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cursor,
    Vector selected)
{
    SDL_Color backgroundColor = { 63, 63, 63, 255 };
    IntegerRender_FillRect(renderer, Vector_New(0, 0), Vector_New(1152, 768), backgroundColor);

    IntegerRender_DrawTexture(renderer,
        sprites,
        Vector_New(0, 0),
        Vector_New(128, 128),
        Vector_New(384, 192),
        Vector_New(384, 384));

    Vector cursorPos = Vector_Scale(Vector_Add(cursor, Vector_New(8, 4)), 48);

    SDL_Color cursorColor = { 255, 255, 255, 255 };
    HudRender_DrawRect(renderer, cursorPos, Vector_New(48, 48), cursorColor);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = Vector_Scale(Vector_Add(selected, Vector_New(8, 4)), 48);

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
            Vector screenPos = Vector_Sub(Vector_Scale(tile->pos, 12), cameraCentered);
            IntegerRender_DrawSelection(renderer, screenPos, 48, color);
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
        Vector linePos = Vector_New(i * 48 - mod.x, 0);

        SDL_Color color = { 255, 255, 255, 63 };
        if (linePos.x + cameraCentered.x == 0)
        {
            color.r = color.b = 0;
            color.a = 127;
        }

        IntegerRender_FillRect(renderer, linePos, Vector_New(3, 768), color);
    }

    for (int i = 0; i < 16 + 1; i++)
    {
        Vector linePos = Vector_New(0, i * 48 - mod.y);

        SDL_Color color = { 255, 255, 255, 63 };
        if (linePos.y + cameraCentered.y == 0)
        {
            color.g = color.b = 0;
            color.a = 127;
        }

        IntegerRender_FillRect(renderer, linePos, Vector_New(1152, 3), color);
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector pos,
    Vector size,
    SDL_Color color)
{
    IntegerRender_FillRect(renderer, pos, Vector_New(3, size.y), color);
    IntegerRender_FillRect(renderer, Vector_Add(pos, Vector_New(size.x - 3, 0)), Vector_New(3, size.y), color);
    IntegerRender_FillRect(renderer, Vector_Add(pos, Vector_New(3, 0)), Vector_New(size.x - 6, 3), color);
    IntegerRender_FillRect(renderer, Vector_Add(pos, Vector_New(3, size.y - 3)), Vector_New(size.x - 6, 3), color);
}
