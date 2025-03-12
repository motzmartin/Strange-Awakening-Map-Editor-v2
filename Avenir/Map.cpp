#include "Map.h"

void Map::Draw(SDL_Renderer* renderer, SDL_Texture* sprites, bool behind, float playerY)
{
    SDL_SetTextureAlphaMod(sprites, 255);

    for (int i = 0; i < tiles.size(); i++)
    {
        if (behind == (!tiles[i].front || tiles[i].pos.y * 4.f < playerY))
        {
            SDL_FRect srcRect = { tiles[i].sprite.x * 16.f, tiles[i].sprite.y * 16.f, 16.f, 16.f };
            SDL_FRect dstRect = { tiles[i].pos.x * 4.f, tiles[i].pos.y * 4.f, 16.f, 16.f };

            SDL_RenderTexture(renderer, sprites, &srcRect, &dstRect);
        }
    }
}

void Map::AddTile(SDL_FPoint position, SDL_FPoint sprite, bool front)
{
    tiles.push_back({ position, sprite, front });
}

void Map::RemoveTile(int index)
{
    tiles.erase(tiles.begin() + index);
}

void Map::SwitchFrontTile(int index)
{
    tiles[index].front = !tiles[index].front;
}

int Map::GetTile(SDL_FPoint pos, SDL_FPoint* tilePos)
{
    for (int i = tiles.size() - 1; i >= 0; i--)
    {
        if (pos.x >= tiles[i].pos.x &&
            pos.y >= tiles[i].pos.y &&
            pos.x < tiles[i].pos.x + 4.f &&
            pos.y < tiles[i].pos.y + 4.f)
        {
            if (tilePos)
            {
                *tilePos = tiles[i].pos;
            }

            return i;
        }
    }

    return -1;
}

void Map::GetFrontTiles(std::vector<SDL_FPoint>* frontTiles)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].front)
        {
            frontTiles->push_back(tiles[i].pos);
        }
    }
}
