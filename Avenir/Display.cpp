#include "Display.h"

Display::Display(int windowWidth, int windowHeight, int texturesNumber)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) return;

    window = SDL_CreateWindow("Avenir", windowWidth, windowHeight, 0);
    if (!window) return;

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) return;

    textureLoader = std::make_unique<TextureLoader>(texturesNumber);

    if (!textureLoader->Load(renderer, "ressource/cursor.png")) return;
    if (!textureLoader->Load(renderer, "ressource/grid.png")) return;
    if (!textureLoader->Load(renderer, "ressource/selection.png")) return;

    SDL_SetRenderVSync(renderer, 1);
    SDL_HideCursor();

    initialized = true;
}

Display::~Display()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Display::Clear()
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
}

void Display::Render()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Display::GetRenderer() const
{
    return renderer;
}

TextureLoader* Display::GetTextureLoader()
{
    return textureLoader.get();
}

bool Display::IsInitialized() const
{
    return initialized;
}
