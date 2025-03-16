#pragma once

#include <SDL3/SDL.h>

#include "GameObjects.h"
#include "DynamicArray.h"
#include "Vector.h"

typedef struct Lights
{
	int quality;

	SDL_Texture* texture;

	Vector pos;
	Vector size;
} Lights;

Lights* Lights_Create(int quality);

void Lights_Process(Lights* lights, DynamicArray** boxes, SDL_Renderer* renderer);
int Lights_GetLightIndexByPos(DynamicArray* lights, Vector pos);

void Lights_Free(Lights* lights);
