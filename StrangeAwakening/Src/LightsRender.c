#include "LightsRender.h"

void LightsRender_Draw(Lights* lights, SDL_Renderer* renderer, Vector cameraCentered)
{
    Render_DrawTexture(renderer,
        lights->texture,
        Vector_New(0, 0),
        Vector_Scale(lights->size, lights->quality),
        Vector_Sub(Vector_Scale(lights->pos, 12), cameraCentered),
        Vector_Scale(lights->size, 12));
}
