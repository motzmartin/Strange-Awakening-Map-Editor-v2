#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class TextureLoader
{
private:
	SDL_Texture** textures = nullptr;

	int currentIndex = 0;

public:
	TextureLoader(int texturesNumber);
	~TextureLoader();

	bool Load(SDL_Renderer* renderer, const char* path);

	SDL_Texture** GetTextures() const;
};
