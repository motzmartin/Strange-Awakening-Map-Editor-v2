#include "VectorConversion.h"

Vector VectorConversion_FromVectorF(VectorF vector)
{
	return Vector_New((int)floorf(vector.x), (int)floorf(vector.y));
}

VectorF VectorConversion_FromVector(Vector vector)
{
	return VectorF_New((float)vector.x, (float)vector.y);
}
