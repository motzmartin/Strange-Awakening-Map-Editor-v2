#include "Vector.h"

Vector Vector_Square(Vector vector, float size)
{
    vector.x = floorf(vector.x / size) * size;
    vector.y = floorf(vector.y / size) * size;

    return vector;
}

Vector Vector_Add(Vector vector1, Vector vector2)
{
    vector1.x += vector2.x;
    vector1.y += vector2.y;

    return vector1;
}

Vector Vector_Sub(Vector vector1, Vector vector2)
{
    vector1.x -= vector2.x;
    vector1.y -= vector2.y;

    return vector1;
}

Vector Vector_Scale(Vector vector, float factor)
{
    vector.x *= factor;
    vector.y *= factor;

    return vector;
}

Vector Vector_Constrain(Vector vector, Vector min, Vector max)
{
    if (vector.x < min.x) vector.x = min.x;
    else if (vector.x > max.x) vector.x = max.x;

    if (vector.y < min.y) vector.y = min.y;
    else if (vector.y > max.y) vector.y = max.y;

    return vector;
}

Vector Vector_Normalize(Vector vector)
{
    Vector result = { 0 };

    float magnitude = sqrtf(powf(vector.x, 2.f) + powf(vector.y, 2.f));
    if (!magnitude) {
        return result;
    }

    result.x = vector.x / magnitude;
    result.y = vector.y / magnitude;

    return result;
}

Vector Vector_Floor(Vector vector)
{
    vector.x = floorf(vector.x);
    vector.y = floorf(vector.y);

    return vector;
}
