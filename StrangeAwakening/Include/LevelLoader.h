#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "GameObjects.h"
#include "DynamicArray.h"
#include "VectorF.h"

void LevelLoader_Save(VectorF spawnPoint, DynamicArray* tiles, DynamicArray** boxes);

void LevelLoader_Load(VectorF* spawnPoint, DynamicArray* oldTiles, DynamicArray** oldBoxes);
