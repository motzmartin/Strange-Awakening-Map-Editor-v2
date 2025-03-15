#pragma once

#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "VectorF.h"

#include "Box.h"

typedef struct Camera
{
	VectorF pos;
} Camera;

Camera* Camera_Create();

void Camera_Update(Camera* camera,
	Uint64 elapsed,
	VectorF playerPos,
	Box** rooms,
	int roomsCursor);
Vector Camera_GetCentered(Camera* camera);

void Camera_Free(Camera* camera);
