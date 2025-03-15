#include "Display.h"

Display* Display_Create(int windowWidth, int windowHeight, int texturesNumber)
{
    Display* display = calloc(1, sizeof(Display));
    if (!display) return NULL;

    if (!SDL_Init(SDL_INIT_VIDEO)) return NULL;

    display->window = SDL_CreateWindow("Avenir", windowWidth, windowHeight, 0);
    if (!display->window) return NULL;

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if (!display->renderer) return NULL;

    display->textureLoader = TextureLoader_Create(texturesNumber);
    if (!display->textureLoader) return NULL;

    if (!TextureLoader_Load(display->textureLoader,
        display->renderer,
        "Assets/Textures/Sprites.png")) return NULL;

    if (!TextureLoader_Load(display->textureLoader,
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
    TextureLoader_Free(display->textureLoader);

    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);

    SDL_Quit();

    free(display);
}
