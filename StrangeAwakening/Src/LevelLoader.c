#include "LevelLoader.h"

void LevelLoader_Save(VectorF spawnPoint, DynamicArray* tiles, DynamicArray** boxes)
{
	FILE* file = fopen("Assets/Levels/Bedroom.lev", "wb");

	fwrite(&spawnPoint, sizeof(VectorF), 1, file);

	fwrite(&tiles->cursor, sizeof(int), 1, file);

	for (int i = 0; i < DynamicArray_GetSize(tiles); i++)
	{
		Tile* tile = DynamicArray_Get(tiles, i);
		fwrite(tile, sizeof(Tile), 1, file);
	}

	for (int i = 0; i < SIZE; i++)
	{
		fwrite(&boxes[i]->cursor, sizeof(int), 1, file);

		for (int j = 0; j < DynamicArray_GetSize(boxes[i]); j++)
		{
			Box* box = DynamicArray_Get(boxes[i], j);
			fwrite(box, sizeof(Box), 1, file);
		}
	}

	fclose(file);
}

void LevelLoader_Load(VectorF* spawnPoint, DynamicArray* oldTiles, DynamicArray** oldBoxes)
{
	FILE* file = fopen("Assets/Levels/Bedroom.lev", "rb");

	fread(spawnPoint, sizeof(VectorF), 1, file);

	int tilesCursor = 0;
	fread(&tilesCursor, sizeof(int), 1, file);

	Tile* tiles = calloc(tilesCursor, sizeof(Tile));
	if (!tiles) return;

	fread(tiles, sizeof(Tile), tilesCursor, file);

	DynamicArray_Clear(oldTiles);

	for (int i = 0; i < tilesCursor; i++)
	{
		Tile* tile = DynamicArray_Add(oldTiles);
		*tile = tiles[i];
	}

	free(tiles);

	for (int i = 0; i < SIZE; i++)
	{
		int boxesCursor = 0;
		fread(&boxesCursor, sizeof(int), 1, file);

		Box* boxes = calloc(boxesCursor, sizeof(Box));
		if (!boxes) return;

		fread(boxes, sizeof(Box), boxesCursor, file);

		DynamicArray_Clear(oldBoxes[i]);

		for (int j = 0; j < boxesCursor; j++)
		{
			Box* box = DynamicArray_Add(oldBoxes[i]);
			*box = boxes[j];
		}

		free(boxes);
	}

	fclose(file);
}
