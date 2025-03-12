#include "Map.h"

void Map::Update(int hoveredX,
    int hoveredY,
    int tileSelectedX,
    int tileSelectedY,
    bool mouseDown)
{
    if (mouseDown)
    {
        tiles.push_back({ hoveredX, hoveredY, tileSelectedX, tileSelectedY, false });
    }
}

void Map::Draw(SDL_Renderer* renderer, SDL_Texture* sprites, bool behind, int playerY)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if ((behind && tiles[i].y < playerY) || (!behind && tiles[i].y >= playerY))
        {
            SDL_Rect srcRect = { tiles[i].spriteX * 16, tiles[i].spriteY * 16, 16, 16 };
            SDL_FRect srcRectF;
            SDL_RectToFRect(&srcRect, &srcRectF);

            SDL_Rect dstRect = { tiles[i].x * 4, tiles[i].y * 4, 16, 16 };
            SDL_FRect dstRectF;
            SDL_RectToFRect(&dstRect, &dstRectF);

            SDL_RenderTexture(renderer, sprites, &srcRectF, &dstRectF);
        }
    }
}

int Map::GetTile(int x, int y, int* tileX, int* tileY)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if (x >= tiles[i].x && y >= tiles[i].y && x < tiles[i].x + 4 && y < tiles[i].y + 4)
        {
            if (tileX) *tileX = tiles[i].x;
            if (tileY) *tileY = tiles[i].y;

            return i;
        }
    }

    return -1;
}

void Map::GetFrontTiles(std::vector<SDL_Point>* frontTiles)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].front)
        {
            frontTiles->push_back({ tiles[i].x, tiles[i].y });
        }
    }
}

void Map::SwitchFrontTile(int index)
{
    tiles[index].front = !tiles[index].front;
}
