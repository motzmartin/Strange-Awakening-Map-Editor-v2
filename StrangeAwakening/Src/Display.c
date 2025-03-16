#include "Display.h"

Display* Display_Create(int windowWidth, int windowHeight, int texturesNumber)
{
    Display* display = calloc(1, sizeof(Display));
    if (!display) return NULL;

    if (!SDL_Init(SDL_INIT_VIDEO)) return NULL;

    display->window = SDL_CreateWindow("SA Map Editor", windowWidth, windowHeight, 0);
    if (!display->window) return NULL;

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if (!display->renderer) return NULL;

    display->textures = DynamicArray_Create(texturesNumber, sizeof(SDL_Texture*));
    if (!display->textures) return NULL;

    if (!TextureLoader_Load(display->textures,
        display->renderer,
        "Assets/Textures/Sprites.png")) return NULL;

    if (!TextureLoader_Load(display->textures,
        display->renderer,
        "Assets/Textures/PlayerSprite.png")) return NULL;

    SDL_SetRenderVSync(display->renderer, 1);
    SDL_SetRenderDrawBlendMode(display->renderer, SDL_BLENDMODE_BLEND);

    return display;
}

void Display_Clear(Display* display, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(display->renderer, r, g, b, 255);
    SDL_RenderClear(display->renderer);
}

void Display_Render(Display* display)
{
    SDL_RenderPresent(display->renderer);
}

void Display_Free(Display* display)
{
    for (int i = 0; i < DynamicArray_GetSize(display->textures); i++)
    {
        SDL_Texture* texture = *(SDL_Texture**)DynamicArray_Get(display->textures, i);
        SDL_DestroyTexture(texture);
    }

    DynamicArray_Free(display->textures);

    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);

    SDL_Quit();

    free(display);
}
