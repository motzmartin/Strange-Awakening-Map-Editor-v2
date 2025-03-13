#include "MapRender.h"

void MapRender_Draw(Map* map,
    SDL_Renderer* renderer,
    SDL_Texture* sprites,
    Vector cameraPos,
    float playerY,
    bool behind)
{
    SDL_SetTextureAlphaMod(sprites, 255);

    for (int i = 0; i < map->cursor; i++)
    {
        Tile* tile = map->tiles[i];

        if (behind == (!tile->front || tile->pos.y < playerY))
        {
            SDL_FRect srcRect = { tile->sprite.x, tile->sprite.y, 16.f, 16.f };
            SDL_FRect dstRect = { tile->pos.x - cameraPos.x, tile->pos.y - cameraPos.y, 48.f, 48.f };
            SDL_RenderTexture(renderer, sprites, &srcRect, &dstRect);
        }
    }
}
