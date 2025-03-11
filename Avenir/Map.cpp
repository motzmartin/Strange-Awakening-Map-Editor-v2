#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Update(int hoveredX,
    int hoveredY,
    int tileSelectedX,
    int tileSelectedY,
    bool mouseDown)
{
    if (mouseDown)
    {
        tiles.push_back({ hoveredX, hoveredY, tileSelectedX, tileSelectedY });
    }
}

void Map::Draw(SDL_Renderer* renderer, SDL_Texture* sprites)
{
    for (int i = 0; i < tiles.size(); i++)
    {
        SDL_FRect srcRect =
        {
            static_cast<float>(tiles[i].spriteX) * 16.f,
            static_cast<float>(tiles[i].spriteY) * 16.f,
            16.f,
            16.f
        };

        SDL_FRect dstRect =
        {
            static_cast<float>(tiles[i].x) * 4.f,
            static_cast<float>(tiles[i].y) * 4.f,
            16.f,
            16.f
        };

        SDL_RenderTexture(renderer, sprites, &srcRect, &dstRect);
    }
}
