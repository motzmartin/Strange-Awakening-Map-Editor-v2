#include "MapRender.h"

void MapRender_Draw(Map* map, SDL_Renderer* renderer, SDL_Texture* sprites, bool behind, float playerY)
{
    SDL_SetTextureAlphaMod(sprites, 255);

    int index = 0;

    while (map->tiles[index])
    {
        Tile* tile = map->tiles[index];

        if (tile && (behind == (!tile->front || tile->pos.y * 4.f < playerY)))
        {
            SDL_FRect srcRect = { tile->sprite.x * 16.f, tile->sprite.y * 16.f, 16.f, 16.f };
            SDL_FRect dstRect = { tile->pos.x * 4.f, tile->pos.y * 4.f, 16.f, 16.f };

            SDL_RenderTexture(renderer, sprites, &srcRect, &dstRect);
        }

        index++;
    }
}
