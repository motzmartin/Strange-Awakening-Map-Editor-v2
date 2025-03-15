#include "LevelLoader.h"

void LevelLoader_Save(Tile** tiles,
	Box** collisions,
	int tilesCursor,
	int collisionsCursor,
	VectorF spawnPoint)
{
	FILE* file = fopen("levels/level1.dat", "wb");

	fwrite(&tilesCursor, sizeof(int), 1, file);

	for (int i = 0; i < tilesCursor; i++)
	{
		fwrite(tiles[i], sizeof(Tile), 1, file);
	}

	fwrite(&collisionsCursor, sizeof(int), 1, file);

	for (int i = 0; i < collisionsCursor; i++)
	{
		fwrite(collisions[i], sizeof(Box), 1, file);
	}

	fwrite(&spawnPoint, sizeof(VectorF), 1, file);

	fclose(file);
}

void LevelLoader_Load(Tile** oldTiles,
	Box** oldCollisions,
	int* oldTilesCursor,
	int* oldCollisionsCursor,
	VectorF* spawnPoint)
{
	FILE* file = fopen("levels/level1.dat", "rb");

	int tilesCursor = 0;
	fread(&tilesCursor, sizeof(int), 1, file);

	Tile* tiles = calloc(tilesCursor, sizeof(Tile));
	if (!tiles) return;
	fread(tiles, sizeof(Tile), tilesCursor, file);

	for (int i = 0; i < tilesCursor; i++)
	{
		if (i < *oldTilesCursor)
		{
			free(oldTiles[i]);
		}

		oldTiles[i] = calloc(1, sizeof(Tile));
		if (!oldTiles[i]) return;

		*oldTiles[i] = tiles[i];
	}

	*oldTilesCursor = tilesCursor;

	int collisionsCursor = 0;
	fread(&collisionsCursor, sizeof(int), 1, file);

	Box* collisions = calloc(collisionsCursor, sizeof(Box));
	if (!collisions) return;
	fread(collisions, sizeof(Box), collisionsCursor, file);

	for (int i = 0; i < collisionsCursor; i++)
	{
		if (i < *oldCollisionsCursor)
		{
			free(oldCollisions[i]);
		}

		oldCollisions[i] = calloc(1, sizeof(Box));
		if (!oldCollisions[i]) return;

		*oldCollisions[i] = collisions[i];
	}

	*oldCollisionsCursor = collisionsCursor;

	fread(spawnPoint, sizeof(VectorF), 1, file);

	fclose(file);
}
