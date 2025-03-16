#pragma once

#include <stdlib.h>
#include <SDL3/SDL.h>

#include "DynamicArray.h"
#include "TextureLoader.h"

typedef struct Display
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	DynamicArray* textures;
} Display;

Display* Display_Create(int windowWidth, int windowHeight, int texturesNumber);

void Display_Clear(Display* display, Uint8 r, Uint8 g, Uint8 b);
void Display_Render(Display* display);

void Display_Free(Display* display);
