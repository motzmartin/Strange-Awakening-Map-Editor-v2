#pragma once

#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "DynamicArray.h"

bool TextureLoader_Load(DynamicArray* textures, SDL_Renderer* renderer, const char* path);
