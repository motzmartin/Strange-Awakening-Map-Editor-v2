#pragma once

#include <SDL3/SDL.h>

#include "Lights.h"

#include "IntegerRender.h"

void LightsRender_Draw(Lights* lights, SDL_Renderer* renderer, Vector cameraCentered);
