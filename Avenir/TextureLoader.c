#include "TextureLoader.h"

TextureLoader* TextureLoader_Create(int texturesNumber)
{
    TextureLoader* textureLoader = calloc(1, sizeof(TextureLoader));
    if (!textureLoader) return NULL;

    textureLoader->textures = calloc(texturesNumber, sizeof(SDL_Texture*));
    if (!textureLoader->textures) return NULL;

    return textureLoader;
}

bool TextureLoader_Load(TextureLoader* textureLoader, SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) return false;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_DestroySurface(loadedSurface);

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    textureLoader->textures[textureLoader->current++] = texture;

    return true;
}

void TextureLoader_Free(TextureLoader* textureLoader)
{
    for (int i = 0; i < textureLoader->current; i++)
    {
        SDL_DestroyTexture(textureLoader->textures[i]);
    }

    free(textureLoader);
}
