#include "Map.h"

Map* Map_Create()
{
    Map* map = calloc(1, sizeof(Map));
    if (!map) return NULL;

    map->tiles = calloc(4096, sizeof(Tile*));
    if (!map->tiles) return NULL;

    return map;
}

void Map_AddTile(Map* map, Vector position, Vector selected, bool front)
{
    if (map->cursor >= 4096) return;

    map->tiles[map->cursor] = calloc(1, sizeof(Tile));
    if (!map->tiles[map->cursor]) return;

    Tile newTile = { position, Vector_Scale(selected, 1.f / 3.f), front };
    *map->tiles[map->cursor++] = newTile;
}

void Map_RemoveTile(Map* map, int index)
{
    free(map->tiles[index]);
    map->tiles[index] = NULL;

    for (int i = index; i < map->cursor - 1; i++)
    {
        map->tiles[i] = map->tiles[i + 1];
    }

    map->tiles[--map->cursor] = NULL;
}

int Map_GetTileIndex(Map* map, Vector position)
{
    for (int i = map->cursor - 1; i >= 0; i--)
    {
        Tile* tile = map->tiles[i];

        if (position.x >= tile->pos.x && position.y >= tile->pos.y &&
            position.x < tile->pos.x + 48.f && position.y < tile->pos.y + 48.f)
        {
            return i;
        }
    }

    return -1;
}

Vector Map_GetTilePosition(Map* map, int index)
{
    return map->tiles[index]->pos;
}

Vector* Map_GetFrontTiles(Map* map, int* frontTilesNumber)
{
    Vector* frontTiles = calloc(4096, sizeof(Vector));
    if (!frontTiles) return NULL;

    int index = 0;

    for (int i = 0; i < map->cursor; i++)
    {
        if (map->tiles[i]->front)
        {
            frontTiles[index++] = map->tiles[i]->pos;
        }
    }

    *frontTilesNumber = index;

    return frontTiles;
}

void Map_SwitchFrontTile(Map* map, int index)
{
    map->tiles[index]->front = !map->tiles[index]->front;
}

void Map_FreeFrontTiles(Vector* frontTiles)
{
    free(frontTiles);
}

void Map_Free(Map* map)
{
    for (int i = 0; i < map->cursor; i++)
    {
        free(map->tiles[i]);
    }
    free(map->tiles);

    free(map);
}
