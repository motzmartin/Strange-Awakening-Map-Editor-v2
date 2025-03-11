#pragma once

#include <memory>
#include <SDL3/SDL.h>

#include "TextureLoader.h"

class Display
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	std::unique_ptr<TextureLoader> textureLoader;

	bool initialized = false;

public:
	Display(int windowWidth, int windowHeight, int texturesNumber);
	~Display();

	void Clear();
	void Render();

	SDL_Renderer* GetRenderer() const;
	TextureLoader* GetTextureLoader();
	bool IsInitialized() const;
};
