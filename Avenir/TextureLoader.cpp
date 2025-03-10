#include "TextureLoader.h"

TextureLoader::TextureLoader(int texturesNumber)
{
    textures = new SDL_Texture * [texturesNumber]();
}

TextureLoader::~TextureLoader()
{
    for (int i = 0; i < currentIndex; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
}

bool TextureLoader::Load(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) return false;

    textures[currentIndex++] = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_DestroySurface(loadedSurface);

    return true;
}

SDL_Texture* TextureLoader::GetTexture(int index) const { return textures[index]; }
