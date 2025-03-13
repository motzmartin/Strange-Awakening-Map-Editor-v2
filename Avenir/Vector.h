#pragma once

#include <math.h>

typedef struct Vector
{
	float x;
	float y;
} Vector;

Vector Vector_Square(Vector vector, float size);
Vector Vector_Add(Vector vector1, Vector vector2);
Vector Vector_Sub(Vector vector1, Vector vector2);
Vector Vector_Scale(Vector vector, float factor);
Vector Vector_Constrain(Vector vector, Vector min, Vector max);
Vector Vector_Normalize(Vector vector);
Vector Vector_Floor(Vector vector);
