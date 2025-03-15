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

	fwrite(&spawnPoint, sizeof(VectorF), 1, file);

	fwrite(&tilesCursor, sizeof(int), 1, file);
	fwrite(&collisionsCursor, sizeof(int), 1, file);
	fwrite(&roomsCursor, sizeof(int), 1, file);;

	for (int i = 0; i < tilesCursor; i++) fwrite(tiles[i], sizeof(Tile), 1, file);
	for (int i = 0; i < collisionsCursor; i++) fwrite(collisions[i], sizeof(Box), 1, file);
	for (int i = 0; i < roomsCursor; i++) fwrite(rooms[i], sizeof(Box), 1, file);

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

	fread(spawnPoint, sizeof(VectorF), 1, file);

	int tilesCursor = 0;
	int collisionsCursor = 0;
	int roomsCursor = 0;

	fread(&tilesCursor, sizeof(int), 1, file);
	fread(&collisionsCursor, sizeof(int), 1, file);
	fread(&roomsCursor, sizeof(int), 1, file);

	*oldTilesCursor = tilesCursor;
	*oldCollisionsCursor = collisionsCursor;
	*oldRoomsCursor = roomsCursor;

	Tile* tiles = calloc(tilesCursor, sizeof(Tile));
	if (!tiles) return;

	Box* collisions = calloc(collisionsCursor, sizeof(Box));
	if (!collisions) return;

	Box* rooms = calloc(roomsCursor, sizeof(Box));
	if (!rooms) return;

	fread(tiles, sizeof(Tile), tilesCursor, file);
	fread(collisions, sizeof(Box), collisionsCursor, file);
	fread(rooms, sizeof(Box), roomsCursor, file);

	for (int i = 0; i < tilesCursor; i++)
	{
		if (i < *oldTilesCursor) free(oldTiles[i]);

		oldTiles[i] = calloc(1, sizeof(Tile));
		if (!oldTiles[i]) return;

		*oldTiles[i] = tiles[i];
	}

	for (int i = 0; i < collisionsCursor; i++)
	{
		if (i < *oldCollisionsCursor) free(oldCollisions[i]);

		oldCollisions[i] = calloc(1, sizeof(Box));
		if (!oldCollisions[i]) return;

		*oldCollisions[i] = collisions[i];
	}

	for (int i = 0; i < roomsCursor; i++)
	{
		if (i < *oldRoomsCursor) free(oldRooms[i]);

		oldRooms[i] = calloc(1, sizeof(Box));
		if (!oldRooms[i]) return;

		*oldRooms[i] = rooms[i];
	}

	free(tiles);
	free(collisions);
	free(rooms);

	fclose(file);
}
