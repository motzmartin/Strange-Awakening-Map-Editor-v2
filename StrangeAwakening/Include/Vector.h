#pragma once

typedef struct Vector
{
	int x;
	int y;
} Vector;

Vector Vector_New(int x, int y);

Vector Vector_Square(Vector vector, int size);

Vector Vector_Add(Vector vector1, Vector vector2);
Vector Vector_Sub(Vector vector1, Vector vector2);

Vector Vector_Scale(Vector vector, int factor);
Vector Vector_Div(Vector vector, int factor);

Vector Vector_Constrain(Vector vector, Vector min, Vector max);
