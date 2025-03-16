#include "TextureLoader.h"

bool TextureLoader_Load(DynamicArray* textures, SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) return false;

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_DestroySurface(loadedSurface);

    SDL_SetTextureScaleMode(newTexture, SDL_SCALEMODE_NEAREST);

    SDL_Texture** texture = (SDL_Texture**)DynamicArray_Add(textures);
    *texture = newTexture;

    return true;
}
