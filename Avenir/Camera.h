#pragma once

#include <stdlib.h>
#include <SDL3/SDL.h>

#include "Vector.h"

typedef struct Camera
{
	Vector pos;
} Camera;

Camera* Camera_Create();

void Camera_Update(Camera* camera, Vector playerPos, Uint64 elapsed);
Vector Camera_GetCentered(Camera* camera);

void Camera_Free(Camera* camera);
