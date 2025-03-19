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
    int optionPointed,
    int mode,
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

        if (mode == 1 && pointed != -1)
        {
            HudRender_DrawRemoveRect(renderer, cameraCentered, tiles, pointed);
        }
        else if (mode == 2)
        {
            HudRender_DrawFrontTiles(renderer, cameraCentered, tiles, pointed);
        }
        else
        {
            Vector screenPos = Vector_Sub(Vector_Scale(cursor, 12), cameraCentered);

            if (mode == 0 && optionPointed == -1)
            {
                HudRender_DrawTilePlacement(renderer, sprites, screenPos, cameraCentered, selected, size);
            }
            else if (mode >= 3 && mode <= 6)
            {
                HudRender_DrawBoxes(renderer, cameraCentered, boxes, screenPos, size, pointed, optionPointed, mode);
            }
        }

        HudRender_DrawOptions(renderer, ui, optionPointed, mode, grid);
    }
}

void HudRender_DrawTilePlacement(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector screenPos,
    Vector cameraCentered,
    Vector selected,
    Vector size)
{
    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            Vector spritePos = Vector_Scale(selected, 16);
            Vector spriteSize = Vector_New(16, 16);
            Vector tilePos = Vector_Add(screenPos, Vector_Scale(Vector_New(j, i), 48));
            Vector tileSize = Vector_New(48, 48);
            Render_DrawTexture(renderer, sprites, spritePos, spriteSize, tilePos, tileSize);
        }
    }
}

void HudRender_DrawBoxes(SDL_Renderer* renderer,
    Vector cameraCentered,
    DynamicArray** boxes,
    Vector screenPos,
    Vector size,
    int pointed,
    int optionPointed,
    int mode)
{
    BoxType type = mode - 3;

    if (pointed == -1 && optionPointed == -1)
    {
        Vector previewBoxSize = Vector_Scale(size, 12);
        SDL_Color previewBoxColor = HudRender_GetBoxColor(type);
        Render_DrawRect(renderer, screenPos, previewBoxSize, previewBoxColor);
    }

    for (int i = 0; i < DynamicArray_GetSize(boxes[type]); i++)
    {
        Box* box = DynamicArray_Get(boxes[type], i);

        Vector boxPos = Vector_Sub(Vector_Scale(box->pos, 12), cameraCentered);
        Vector boxSize = Vector_Scale(box->size, 12);
        SDL_Color boxColor = HudRender_GetBoxColor(type);
        if (i == pointed)
        {
            boxColor.r = 255;
            boxColor.g = boxColor.b = 0;
        }
        Render_DrawRect(renderer, boxPos, boxSize, boxColor);
    }
}

void HudRender_DrawInventory(SDL_Renderer* renderer, SDL_Texture* sprites, Vector cursor, Vector selected)
{
    Vector backgroundPos = Vector_New(0, 0);
    Vector backgroundSize = Vector_New(1152, 768);
    SDL_Color backgroundColor = { 63, 63, 63, 255 };
    Render_FillRect(renderer, backgroundPos, backgroundSize, backgroundColor);

    Vector spritePos = Vector_New(0, 0);
    Vector spriteSize = Vector_New(128, 128);
    Vector inventoryPos = Vector_New(384, 192);
    Vector inventorySize = Vector_New(384, 384);
    Render_DrawTexture(renderer, sprites, spritePos, spriteSize, inventoryPos, inventorySize);

    Vector pointedPos = Vector_Scale(Vector_Add(cursor, Vector_New(8, 4)), 48);
    Vector pointedSize = Vector_New(48, 48);
    SDL_Color pointedColor = { 255, 255, 255, 255 };
    Render_DrawRect(renderer, pointedPos, pointedSize, pointedColor);

    if (cursor.x != selected.x || cursor.y != selected.y)
    {
        Vector selectedPos = Vector_Scale(Vector_Add(selected, Vector_New(8, 4)), 48);
        Vector selectedSize = Vector_New(48, 48);
        SDL_Color selectedColor = { 0, 255, 0, 255 };
        Render_DrawRect(renderer, selectedPos, selectedSize, selectedColor);
    }
}

void HudRender_DrawOptions(SDL_Renderer* renderer, SDL_Texture* ui, int optionPointed, int mode, bool grid)
{
    for (int i = 0; i < 13; i++)
    {
        Vector spritePos = Vector_New(i * 8, 0);
        Vector spriteSize = Vector_New(8, 8);
        Vector optionPos = Vector_New(i < 8 ? (i * 30 + 6) : (1152 - (13 - i) * 30 - 6), 768 - 30 - 6);
        Vector optionSize = Vector_New(24, 24);
        Render_DrawTexture(renderer, ui, spritePos, spriteSize, optionPos, optionSize);

        if (i == optionPointed || (i < 8 ? (i == mode) : (i == 8 && grid)))
        {
            Vector rectPos = Vector_Sub(optionPos, Vector_New(3, 3));
            Vector rectSize = Vector_Add(optionSize, Vector_New(6, 6));
            SDL_Color rectColor = { 255, 255, 255, 255 };
            Render_DrawRect(renderer, rectPos, rectSize, rectColor);
        }
    }
}

void HudRender_DrawRemoveRect(SDL_Renderer* renderer, Vector cameraCentered, DynamicArray* tiles, int pointed)
{
    Tile* pointedTile = DynamicArray_Get(tiles, pointed);

    Vector rectPos = Vector_Sub(Vector_Scale(pointedTile->pos, 12), cameraCentered);
    Vector rectSize = Vector_New(48, 48);
    SDL_Color rectColor = { 255, 0, 0, 255 };
    Render_DrawRect(renderer, rectPos, rectSize, rectColor);
}

void HudRender_DrawFrontTiles(SDL_Renderer* renderer, Vector cameraCentered, DynamicArray* tiles, int pointed)
{
    for (int i = 0; i < DynamicArray_GetSize(tiles); i++)
    {
        Tile* tile = DynamicArray_Get(tiles, i);

        if (tile->front || i == pointed)
        {
            Vector selectionPos = Vector_Sub(Vector_Scale(tile->pos, 12), cameraCentered);
            Vector selectionSize = Vector_New(48, 48);
            SDL_Color selectionColor = { 255, 255, 255, 255 };
            if (tile->front && i == pointed)
            {
                selectionColor.g = selectionColor.b = 0;
            }
            else if (tile->front)
            {
                selectionColor.b = 0;
            }
            Render_DrawSelection(renderer, selectionPos, selectionSize, selectionColor);
        }
    }
}

void HudRender_DrawGrid(SDL_Renderer* renderer, Vector cameraCentered)
{
    Vector mod = Vector_Mod(cameraCentered, Vector_New(48, 48));

    for (int i = 0; i < 24 + 1; i++)
    {
        Vector linePos = Vector_New(i * 48 - mod.x, 0);
        Vector lineSize = Vector_New(3, 768);
        SDL_Color lineColor = { 255, 255, 255, 63 };
        if (linePos.x + cameraCentered.x == 0)
        {
            lineColor.r = lineColor.b = 0;
            lineColor.a = 127;
        }
        Render_FillRect(renderer, linePos, lineSize, lineColor);
    }

    for (int i = 0; i < 16 + 1; i++)
    {
        Vector linePos = Vector_New(0, i * 48 - mod.y);
        Vector lineSize = Vector_New(1552, 3);
        SDL_Color lineColor = { 255, 255, 255, 63 };
        if (linePos.y + cameraCentered.y == 0)
        {
            lineColor.g = lineColor.b = 0;
            lineColor.a = 127;
        }
        Render_FillRect(renderer, linePos, lineSize, lineColor);
    }
}

SDL_Color HudRender_GetBoxColor(BoxType type)
{
    SDL_Color color = { 255, 255, 255, 255 };

    switch (type)
    {
    case COLLISIONS:
        color.r = color.g = 0;
        break;
    case ROOMS:
        color.g = 0;
        break;
    case LIGHTS:
        color.r = 0;
        break;
    case EMIT_LIGHTS:
        color.b = 0;
    }

    return color;
}
