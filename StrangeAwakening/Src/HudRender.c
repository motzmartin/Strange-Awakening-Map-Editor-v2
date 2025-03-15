#include "HudRender.h"

void HudRender_Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    Vector cursor,
    Vector selected,
    Vector collisionSize,
    Vector roomSize,
    Vector lightSize,
    Tile** tiles,
    Box** collisions,
    Box** rooms,
    Light** lights,
    int tilesCursor,
    int collisionsCursor,
    int roomsCursor,
    int lightsCursor,
    int tilePointed,
    int collisionPointed,
    int roomPointed,
    int lightPointed,
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
            if (tilePointed != -1)
            {
                Tile* tile = tiles[tilePointed];

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
                HudRender_DrawFrontTiles(renderer,
                    cameraCentered,
                    tiles,
                    tilesCursor,
                    tilePointed);
            }
        }
        else if (mode == 4 || mode == 5 || mode == 6)
        {
            Vector cursorPos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };

            if (mode == 4)
            {
                if (collisionPointed == -1)
                {
                    HudRender_DrawRect(renderer, cursorPos, Vector_Scale(collisionSize, 12), 0, 0, 255, 255);
                }

                HudRender_DrawCollisions(renderer,
                    cameraCentered,
                    collisions,
                    collisionsCursor,
                    collisionPointed);
            }
            else if (mode == 5)
            {
                if (roomPointed == -1)
                {
                    HudRender_DrawRect(renderer, cursorPos, Vector_Scale(roomSize, 12), 255, 0, 255, 255);
                }

                HudRender_DrawRooms(renderer,
                    cameraCentered,
                    rooms,
                    roomsCursor,
                    roomPointed);
            }
            else if (mode == 6)
            {
                if (lightPointed == -1)
                {
                    HudRender_DrawRect(renderer, cursorPos, Vector_Scale(lightSize, 12), 0, 255, 255, 255);
                }

                HudRender_DrawLights(renderer,
                    cameraCentered,
                    lights,
                    lightsCursor,
                    lightPointed);
            }
        }
        else
        {
            Vector cursorPos = { cursor.x * 12 - cameraCentered.x, cursor.y * 12 - cameraCentered.y };

            SDL_Rect tileSrc = { selected.x * 16, selected.y * 16, 16, 16 };
            SDL_Rect tileDst = { cursorPos.x, cursorPos.y, 48, 48 };
            IntegerRender_DrawSprite(renderer, sprites, tileSrc, tileDst);
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
    IntegerRender_DrawSprite(renderer, sprites, inventorySrc, inventoryDst);

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
    Tile** tiles,
    int tilesCursor,
    int tilePointed)
{
    for (int i = 0; i < tilesCursor; i++)
    {
        Tile* tile = tiles[i];

        if (tile->front && i != tilePointed)
        {
            Vector frontPos = { tile->pos.x * 12 - cameraCentered.x, tile->pos.y * 12 - cameraCentered.y };
            HudRender_DrawRect(renderer, frontPos, Vector_New(48, 48), 255, 255, 0, 255);
        }
    }
}

void HudRender_DrawCollisions(SDL_Renderer* renderer,
    Vector cameraCentered,
    Box** collisions,
    int collisionsCursor,
    int collisionPointed)
{
    for (int i = 0; i < collisionsCursor; i++)
    {
        Box* box = collisions[i];

        Vector collisionPos = { box->pos.x * 12 - cameraCentered.x, box->pos.y * 12 - cameraCentered.y };
        
        Uint8 r = 0;
        Uint8 b = 255;

        if (i == collisionPointed)
        {
            r = 255;
            b = 0;
        }

        HudRender_DrawRect(renderer, collisionPos, Vector_Scale(box->size, 12), r, 0, b, 255);
    }
}

void HudRender_DrawRooms(SDL_Renderer* renderer,
    Vector cameraCentered,
    Box** rooms,
    int roomsCursor,
    int roomPointed)
{
    for (int i = 0; i < roomsCursor; i++)
    {
        Box* box = rooms[i];

        Vector roomPos = { box->pos.x * 12 - cameraCentered.x, box->pos.y * 12 - cameraCentered.y };

        Uint8 r = 255;
        Uint8 b = 255;

        if (i == roomPointed)
        {
            b = 0;
        }

        HudRender_DrawRect(renderer, roomPos, Vector_Scale(box->size, 12), r, 0, b, 255);
    }
}

void HudRender_DrawLights(SDL_Renderer* renderer,
    Vector cameraCentered,
    Light** lights,
    int lightsCursor,
    int lightPointed)
{
    for (int i = 0; i < lightsCursor; i++)
    {
        Light* light = lights[i];

        Vector roomPos = { light->pos.x * 12 - cameraCentered.x, light->pos.y * 12 - cameraCentered.y };
        Vector roomSize = Vector_Scale(light->size, 12);

        Uint8 r = 0;
        Uint8 g = 255;
        Uint8 b = 255;

        if (i == lightPointed)
        {
            r = 255;
            g = 0;
            b = 0;
        }

        if (light->emit)
        {
            SDL_Rect rect = { roomPos.x, roomPos.y, roomSize.x, roomSize.y };
            IntegerRender_FillRect(renderer, rect, r, g, b, 255);
        }
        else
        {
            HudRender_DrawRect(renderer, roomPos, roomSize, r, g, b, 255);
        }
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
            r = 0;
            b = 0;
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
            g = 0;
            b = 0;
            a = 127;
        }

        IntegerRender_FillRect(renderer, rect, r, g, b, a);
    }
}

void HudRender_DrawRect(SDL_Renderer* renderer,
    Vector position,
    Vector size,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a)
{
    SDL_Rect leftSide = { position.x, position.y, 3, size.y };
    SDL_Rect rightSide = { position.x + size.x - 3, position.y, 3, size.y };

    SDL_Rect topSide = { position.x + 3, position.y, size.x - 6, 3 };
    SDL_Rect bottomSide = { position.x + 3, position.y + size.y - 3, size.x - 6, 3 };

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
