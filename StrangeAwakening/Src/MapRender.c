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
            IntegerRender_DrawTexture(renderer,
                sprites,
                Vector_Scale(tile->sprite, 16),
                Vector_New(16, 16),
                Vector_Sub(Vector_Scale(tile->pos, 12), cameraCentered),
                Vector_New(48, 48));
        }
    }
}
