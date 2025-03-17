#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "VectorF.h"
#include "VectorConversion.h"

typedef struct InterfaceEvents
{
	Uint8* keyboard;
	Vector mouse;

	bool* events;
	int eventsNumber;
} InterfaceEvents;

InterfaceEvents* InterfaceEvents_Create(int eventsNumber);

bool InterfaceEvents_Poll(InterfaceEvents* interfaceEvents);
void InterfaceEvents_Clear(InterfaceEvents* interfaceEvents);

void InterfaceEvents_Free(InterfaceEvents* interfaceEvents);
