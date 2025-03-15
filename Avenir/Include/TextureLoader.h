#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct TextureLoader
{
	SDL_Texture** textures;
	int cursor;
} TextureLoader;

TextureLoader* TextureLoader_Create(int texturesNumber);

bool TextureLoader_Load(TextureLoader* textureLoader, SDL_Renderer* renderer, const char* path);

void TextureLoader_Free(TextureLoader* textureLoader);
