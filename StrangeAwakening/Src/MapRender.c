#include "MapRender.h"

void MapRender_Draw(Map* map,
    SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraCentered,
    float playerY,
    bool behind)
{
    for (int i = 0; i < DynamicArray_GetSize(map->tiles); i++)
    {
        Tile* tile = DynamicArray_Get(map->tiles, i);

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
            IntegerRender_DrawTexture(renderer, sprites, srcRect, dstRect);
        }
    }
}
