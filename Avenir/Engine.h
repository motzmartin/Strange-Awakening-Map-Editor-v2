#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "Display.h"
#include "InterfaceEvents.h"
#include "Game.h"

typedef struct Engine
{
	Display* display;
	InterfaceEvents* interfaceEvents;
	Game* game;

	bool running;
} Engine;

Engine* Engine_Create(int windowWidth,
	int windowHeight,
	int eventsNumber,
	int texturesNumber);

void Engine_Update(Engine* engine);
void Engine_Render(Engine* engine);

void Engine_Free(Engine* engine);
