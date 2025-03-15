#pragma once

#include <stdlib.h>

#include "Vector.h"

typedef struct Light
{
	Vector pos;
	Vector size;

	bool emit;
} Light;
