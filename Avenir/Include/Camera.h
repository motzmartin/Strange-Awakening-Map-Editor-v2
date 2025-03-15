#pragma once

#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "VectorF.h"

typedef struct Camera
{
	VectorF pos;
} Camera;

Camera* Camera_Create();

void Camera_Update(Camera* camera, VectorF playerPos, Uint64 elapsed);
Vector Camera_GetCentered(Camera* camera);

void Camera_Free(Camera* camera);
