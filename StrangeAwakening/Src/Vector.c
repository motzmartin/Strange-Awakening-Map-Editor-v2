#include "Vector.h"

Vector Vector_New(int x, int y)
{
    Vector vector = { x, y };

    return vector;
}

bool Vector_AreEqual(Vector vector1, Vector vector2)
{
    return vector1.x == vector2.x && vector1.y == vector2.y;
}

bool Vector_IsZero(Vector vector)
{
    return Vector_AreEqual(vector, Vector_New(0, 0));
}

Vector Vector_Square(Vector vector, int size)
{
    vector.x = (vector.x / size) * size;
    vector.y = (vector.y / size) * size;

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

Vector Vector_Scale(Vector vector, int factor)
{
    vector.x *= factor;
    vector.y *= factor;

    return vector;
}

Vector Vector_Div(Vector vector, int factor)
{
    if (vector.x < 0) vector.x = (vector.x - (factor - 1)) / factor;
    else vector.x /= factor;

    if (vector.y < 0) vector.y = (vector.y - (factor - 1)) / factor;
    else vector.y /= factor;

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
