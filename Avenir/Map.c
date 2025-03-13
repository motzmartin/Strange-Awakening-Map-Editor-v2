#include "Map.h"

Map* Map_Create()
{
    Map* map = calloc(1, sizeof(Map));
    if (!map) return NULL;

    map->tiles = calloc(1024, sizeof(Tile*));
    if (!map->tiles) return NULL;

    return map;
}

void Map_AddTile(Map* map, Position position, Position sprite, bool front)
{
    int index = 0;

    while (map->tiles[index])
    {
        index++;
    }

    map->tiles[index] = calloc(1, sizeof(Tile));
    if (!map->tiles[index]) return;

    Tile newTile = { position, sprite, front };
    *map->tiles[index] = newTile;
}

void Map_RemoveTile(Map* map, int index)
{
    if (!map->tiles[index]) return;

    free(map->tiles[index]);

    map->tiles[index] = NULL;
}

void Map_SwitchFrontTile(Map* map, int index)
{
    map->tiles[index]->front = !map->tiles[index]->front;
}

int Map_GetTile(Map* map, Position pos, Position* tilePos)
{
    int index = 0;

    while (map->tiles[index])
    {
        Tile* tile = map->tiles[index];

        if (pos.x >= tile->pos.x &&
            pos.y >= tile->pos.y &&
            pos.x < tile->pos.x + 4.f &&
            pos.y < tile->pos.y + 4.f)
        {
            if (tilePos)
            {
                *tilePos = tile->pos;
            }

            return index;
        }

        index++;
    }

    return -1;
}

Position** Map_GetFrontTiles(Map* map)
{
    Position** frontTiles = calloc(1024, sizeof(Position*));
    if (!frontTiles) return NULL;

    int index = 0;
    int frontTilesIndex = 0;

    while (map->tiles[index])
    {
        if (map->tiles[index]->front)
        {
            Position* frontTile = calloc(1, sizeof(Position));
            if (!frontTile)
            {
                Map_FreeFrontTiles(frontTiles);
                return NULL;
            }

            *frontTile = map->tiles[index]->pos;

            frontTiles[frontTilesIndex++] = frontTile;
        }

        index++;
    }

    return frontTiles;
}

void Map_FreeFrontTiles(Position** frontTiles)
{
    if (!frontTiles)
    {
        return;
    }

    int index = 0;

    while (frontTiles[index])
    {
        free(frontTiles[index]);

        index++;
    }

    free(frontTiles);
}

void Map_Free(Map* map)
{
    for (int i = 0; i < 1024; i++)
    {
        Map_RemoveTile(map, i);
    }

    free(map->tiles);

    free(map);
}
