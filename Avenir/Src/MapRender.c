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

        if (behind == (!tile->front || tile->pos.y * 12 < (int)floorf(playerY)))
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
