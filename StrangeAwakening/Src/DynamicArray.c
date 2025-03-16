#include "DynamicArray.h"

DynamicArray* DynamicArray_Create(int size, int elementSize)
{
    DynamicArray* array = calloc(1, sizeof(DynamicArray));
    if (!array) return NULL;

    array->arr = calloc(size, sizeof(void*));
    if (!array->arr) return NULL;

    array->size = size;
    array->elementSize = elementSize;

    return array;
}

void* DynamicArray_Add(DynamicArray* array)
{
    if (array->cursor == array->size) return NULL;

    array->arr[array->cursor] = calloc(1, array->elementSize);
    if (!array->arr[array->cursor]) return NULL;

    return array->arr[array->cursor++];
}

void* DynamicArray_Get(DynamicArray* array, int index)
{
    return array->arr[index];
}

void DynamicArray_Remove(DynamicArray* array, int index)
{
    free(array->arr[index]);
    array->arr[index] = NULL;

    for (int i = index; i < array->cursor - 1; i++)
    {
        array->arr[i] = array->arr[i + 1];
    }

    array->arr[--array->cursor] = NULL;
}

void DynamicArray_Clear(DynamicArray* array)
{
    for (int i = 0; i < array->cursor; i++)
    {
        free(array->arr[i]);
    }

    array->cursor = 0;
}

int DynamicArray_GetSize(DynamicArray* array)
{
    return array->cursor;
}

bool DynamicArray_IsEmpty(DynamicArray* array)
{
    return !array->cursor;
}

void DynamicArray_Free(DynamicArray* array)
{
    for (int i = 0; i < array->cursor; i++)
    {
        free(array->arr[i]);
    }

    free(array->arr);

    free(array);
}
