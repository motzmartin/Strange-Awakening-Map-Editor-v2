#pragma once

#include <stdbool.h>
#include <math.h>

#include "Vector.h"

typedef struct VectorF
{
	float x;
	float y;
} VectorF;

VectorF VectorF_New(float x, float y);

bool VectorF_AreEqual(VectorF vector1, VectorF vector2);

VectorF VectorF_Add(VectorF vector1, VectorF vector2);
VectorF VectorF_Sub(VectorF vector1, VectorF vector2);

VectorF VectorF_Scale(VectorF vector, float factor);
VectorF VectorF_Div(VectorF vector, float factor);

VectorF VectorF_Constrain(VectorF vector, VectorF min, VectorF max);

VectorF VectorF_Normalize(VectorF vector);

VectorF VectorF_FromVector(Vector vector);
