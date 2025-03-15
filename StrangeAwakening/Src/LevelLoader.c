#include "LevelLoader.h"

void LevelLoader_Save(Tile** tiles,
	Box** collisions,
	Box** rooms,
	int tilesCursor,
	int collisionsCursor,
	int roomsCursor,
	VectorF spawnPoint)
{
	FILE* file = fopen("Assets/Levels/Bedroom.lev", "wb");

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

	fwrite(&roomsCursor, sizeof(int), 1, file);

	for (int i = 0; i < roomsCursor; i++)
	{
		fwrite(rooms[i], sizeof(Box), 1, file);
	}

	fwrite(&spawnPoint, sizeof(VectorF), 1, file);

	fclose(file);
}

void LevelLoader_Load(Tile** oldTiles,
	Box** oldCollisions,
	Box** oldRooms,
	int* oldTilesCursor,
	int* oldCollisionsCursor,
	int* oldRoomsCursor,
	VectorF* spawnPoint)
{
	FILE* file = fopen("Assets/Levels/Bedroom.lev", "rb");

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
	free(tiles);
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
	free(collisions);
	*oldCollisionsCursor = collisionsCursor;

	int roomsCursor = 0;
	fread(&roomsCursor, sizeof(int), 1, file);
	Box* rooms = calloc(roomsCursor, sizeof(Box));
	if (!rooms) return;
	fread(rooms, sizeof(Box), roomsCursor, file);
	for (int i = 0; i < roomsCursor; i++)
	{
		if (i < *oldRoomsCursor)
		{
			free(oldRooms[i]);
		}

		oldRooms[i] = calloc(1, sizeof(Box));
		if (!oldRooms[i]) return;

		*oldRooms[i] = rooms[i];
	}
	free(rooms);
	*oldRoomsCursor = roomsCursor;

	fread(spawnPoint, sizeof(VectorF), 1, file);

	fclose(file);
}
