#include "LightsRender.h"

void LightsRender_Draw(Lights* lights, SDL_Renderer* renderer, Vector cameraCentered)
{
    if (lights->texture)
    {
        SDL_Rect lightsSrc = { 0, 0, lights->size.x * lights->quality, lights->size.y * lights->quality };
        SDL_Rect lightsDst =
        {
            lights->pos.x * 12 - cameraCentered.x,
            lights->pos.y * 12 - cameraCentered.y,
            lights->size.x * 12,
            lights->size.y * 12
        };
        IntegerRender_DrawTexture(renderer, lights->texture, lightsSrc, lightsDst);
    }
}
