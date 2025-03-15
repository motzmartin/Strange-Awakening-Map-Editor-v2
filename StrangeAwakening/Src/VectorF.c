#include "VectorF.h"

VectorF VectorF_New(float x, float y)
{
    VectorF vector = { x, y };

    return vector;
}

VectorF VectorF_Add(VectorF vector1, VectorF vector2)
{
    vector1.x += vector2.x;
    vector1.y += vector2.y;

    return vector1;
}

VectorF VectorF_Sub(VectorF vector1, VectorF vector2)
{
    vector1.x -= vector2.x;
    vector1.y -= vector2.y;

    return vector1;
}

VectorF VectorF_Scale(VectorF vector, float factor)
{
    vector.x *= factor;
    vector.y *= factor;

    return vector;
}

VectorF VectorF_Div(VectorF vector, float factor)
{
    vector.x /= factor;
    vector.y /= factor;

    return vector;
}

VectorF VectorF_Constrain(VectorF vector, VectorF min, VectorF max)
{
    if (vector.x < min.x) vector.x = min.x;
    else if (vector.x > max.x) vector.x = max.x;

    if (vector.y < min.y) vector.y = min.y;
    else if (vector.y > max.y) vector.y = max.y;

    return vector;
}

VectorF VectorF_Normalize(VectorF vector)
{
    VectorF result = { 0 };

    float magnitude = sqrtf(powf(vector.x, 2.f) + powf(vector.y, 2.f));
    if (!magnitude) {
        return result;
    }

    result.x = vector.x / magnitude;
    result.y = vector.y / magnitude;

    return result;
}
