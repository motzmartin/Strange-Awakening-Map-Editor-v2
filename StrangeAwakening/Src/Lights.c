#include "Lights.h"

Lights* Lights_Create(int quality)
{
    Lights* lights = calloc(1, sizeof(Lights));
    if (!lights) return NULL;

    lights->quality = quality;

    return lights;
}

void Lights_Process(Lights* lights, DynamicArray** boxes, SDL_Renderer* renderer)
{
    if (lights->texture)
    {
        SDL_DestroyTexture(lights->texture);
        lights->texture = NULL;
    }

    if (DynamicArray_IsEmpty(boxes[LIGHTS]))
    {
        return;
    }

    Box* first = DynamicArray_Get(boxes[LIGHTS], 0);

    Vector min = first->pos;
    Vector max = first->pos;

    for (int i = 0; i < DynamicArray_GetSize(boxes[LIGHTS]); i++)
    {
        Box* light = DynamicArray_Get(boxes[LIGHTS], i);

        if (light->pos.x < min.x) min.x = light->pos.x;
        if (light->pos.y < min.y) min.y = light->pos.y;

        if (light->pos.x + light->size.x > max.x) max.x = light->pos.x + light->size.x;
        if (light->pos.y + light->size.y > max.y) max.y = light->pos.y + light->size.y;
    }

    Vector size = Vector_Sub(max, min);
    Vector realSize = Vector_Scale(size, lights->quality);

    lights->pos = min;
    lights->size = size;

    float** lightsTmp = calloc(realSize.y, sizeof(float*));
    if (!lightsTmp) return;

    for (int i = 0; i < realSize.y; i++)
    {
        lightsTmp[i] = calloc(realSize.x, sizeof(float));
        if (!lightsTmp[i]) return;
    }

    float intensity = 1.0f;

    for (int i = 0; i < DynamicArray_GetSize(boxes[EMIT_LIGHTS]); i++)
    {
        Box* emitLight = DynamicArray_Get(boxes[EMIT_LIGHTS], i);

        for (int j = 0; j < emitLight->size.y; j++)
        {
            for (int k = 0; k < emitLight->size.x; k++)
            {
                for (int l = 0; l < lights->quality; l++)
                {
                    for (int m = 0; m < lights->quality; m++)
                    {
                        int y = (j + emitLight->pos.y - min.y) * lights->quality + l;
                        int x = (k + emitLight->pos.x - min.x) * lights->quality + m;

                        if (x >= 0 && x < realSize.x &&
                            y >= 0 && y < realSize.y)
                        {
                            lightsTmp[y][x] = intensity;
                        }
                    }
                }
            }
        }
    }

    intensity -= 0.02f / (float)lights->quality;

    while (intensity > 0.f)
    {
        float** temp = calloc(realSize.y, sizeof(float*));
        if (!temp) return;

        for (int i = 0; i < realSize.y; i++)
        {
            temp[i] = calloc(realSize.x, sizeof(float));
            if (!temp[i]) return;

            for (int j = 0; j < realSize.x; j++)
            {
                temp[i][j] = lightsTmp[i][j];
            }
        }

        for (int i = 0; i < realSize.y; i++)
        {
            for (int j = 0; j < realSize.x; j++)
            {
                Vector pos = Vector_New(min.x + j / lights->quality, min.y + i / lights->quality);
                bool canSpread = Lights_CanSpreadAtPos(boxes[LIGHTS], pos);

                if (temp[i][j] == 0 && canSpread)
                {
                    if ((j > 0 && temp[i][j - 1] > 0) ||
                        (i > 0 && temp[i - 1][j] > 0) ||
                        (j < realSize.x - 1 && temp[i][j + 1] > 0) ||
                        (i < realSize.y - 1 && temp[i + 1][j] > 0))
                    {
                        lightsTmp[i][j] = intensity;
                    }
                }
            }
        }

        intensity -= 0.02f / (float)lights->quality;

        for (int i = 0; i < realSize.y; i++)
        {
            free(temp[i]);
        }

        free(temp);
    }

    lights->texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        realSize.x,
        realSize.y);
    if (!lights->texture) return;

    SDL_SetTextureScaleMode(lights->texture, SDL_SCALEMODE_NEAREST);

    const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);

    Uint32* pixels = NULL;
    int pitch = 0;

    SDL_LockTexture(lights->texture, NULL, &pixels, &pitch);

    for (int i = 0; i < realSize.y; i++)
    {
        for (int j = 0; j < realSize.x; j++)
        {
            Uint8 alpha = 255 - (Uint8)(lightsTmp[i][j] * 255.f);
            pixels[i * realSize.x + j] = SDL_MapRGBA(format, NULL, 0, 0, 0, alpha);
        }
    }

    SDL_UnlockTexture(lights->texture);

    for (int i = 0; i < realSize.y; i++)
    {
        free(lightsTmp[i]);
    }

    free(lightsTmp);
}

bool Lights_CanSpreadAtPos(DynamicArray* lights, Vector pos)
{
    for (int i = DynamicArray_GetSize(lights) - 1; i >= 0; i--)
    {
        Box* light = DynamicArray_Get(lights, i);

        if (pos.x >= light->pos.x &&
            pos.y >= light->pos.y &&
            pos.x < light->pos.x + light->size.x &&
            pos.y < light->pos.y + light->size.y)
        {
            return true;
        }
    }

    return false;
}

void Lights_Free(Lights* lights)
{
    free(lights);
}
