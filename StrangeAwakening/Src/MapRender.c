#include "MapRender.h"

void MapRender_Draw(Map* map,
    SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    float playerY,
    bool behind)
{
    for (int i = 0; i < map->tilesCursor; i++)
    {
        Tile* tile = map->tiles[i];

        if (behind == (!tile->front || (float)tile->pos.y * 12.f < playerY))
        {
            SDL_Rect srcRect = { tile->sprite.x * 16, tile->sprite.y * 16, 16, 16 };
            SDL_Rect dstRect =
            {
                tile->pos.x * 12 - cameraCentered.x,
                tile->pos.y * 12 - cameraCentered.y,
                48,
                48
            };
            IntegerRender_DrawSprite(renderer, sprites, srcRect, dstRect);
        }
    }
}

void MapRender_DrawLights(Map* map, SDL_Renderer* renderer, Vector cameraCentered)
{
    if (map->lightsTexture)
    {
        SDL_Rect lightsSrc = { 0, 0, map->lightsSize.x, map->lightsSize.y };
        SDL_Rect lightsDst =
        {
            map->lightsPos.x * 12 - cameraCentered.x,
            map->lightsPos.y * 12 - cameraCentered.y,
            map->lightsSize.x * 12,
            map->lightsSize.y * 12
        };
        IntegerRender_DrawSprite(renderer, map->lightsTexture, lightsSrc, lightsDst);
    }
}
