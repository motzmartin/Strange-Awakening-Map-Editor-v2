#pragma once

#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "GameObjects.h"
#include "DynamicArray.h"
#include "Vector.h"
#include "VectorF.h"

typedef struct Camera
{
	VectorF pos;
} Camera;

Camera* Camera_Create();

void Camera_Update(Camera* camera, VectorF playerPos, DynamicArray* rooms, float elapsed);

Vector Camera_GetCentered(Camera* camera);

void Camera_Free(Camera* camera);
