#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct DynamicArray
{
	void** arr;
	int cursor;

	int size;
	int elementSize;
} DynamicArray;

DynamicArray* DynamicArray_Create(int size, int elementSize);

void* DynamicArray_Add(DynamicArray* array);
void* DynamicArray_Get(DynamicArray* array, int index);
void DynamicArray_Remove(DynamicArray* array, int index);
void DynamicArray_Clear(DynamicArray* array);

int DynamicArray_GetSize(DynamicArray* array);
bool DynamicArray_IsEmpty(DynamicArray* array);

void DynamicArray_Free(DynamicArray* array);
