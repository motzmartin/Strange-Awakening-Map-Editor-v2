#include "Map.h"

Map* Map_Create(int size)
{
    Map* map = calloc(1, sizeof(Map));
    if (!map) return NULL;

    map->tiles = calloc(size, sizeof(Tile*));
    if (!map->tiles) return NULL;

    map->collisions = calloc(size, sizeof(Box*));
    if (!map->collisions) return NULL;

    map->size = size;

    return map;
}

void Map_AddTile(Map* map, Vector position, Vector selected, bool front)
{
    if (map->tilesCursor == map->size) return;

    map->tiles[map->tilesCursor] = calloc(1, sizeof(Tile));
    if (!map->tiles[map->tilesCursor]) return;

    Tile newTile = { position, selected, front };
    *map->tiles[map->tilesCursor++] = newTile;
}

void Map_RemoveTile(Map* map, int index)
{
    free(map->tiles[index]);
    map->tiles[index] = NULL;

    for (int i = index; i < map->tilesCursor - 1; i++)
    {
        map->tiles[i] = map->tiles[i + 1];
    }

    map->tiles[--map->tilesCursor] = NULL;
}

void Map_AddCollision(Map* map, Vector position, Vector size)
{
    if (map->collisionsCursor == map->size) return;

    map->collisions[map->collisionsCursor] = calloc(1, sizeof(Box));
    if (!map->collisions[map->collisionsCursor]) return;

    Box newCollision = { position, size };
    *map->collisions[map->collisionsCursor++] = newCollision;
}

void Map_RemoveCollision(Map* map, int index)
{
    free(map->collisions[index]);
    map->collisions[index] = NULL;

    for (int i = index; i < map->collisionsCursor - 1; i++)
    {
        map->collisions[i] = map->collisions[i + 1];
    }

    map->collisions[--map->collisionsCursor] = NULL;
}

int Map_GetTileIndex(Map* map, Vector position)
{
    for (int i = map->tilesCursor - 1; i >= 0; i--)
    {
        Tile* tile = map->tiles[i];

        if (position.x >= tile->pos.x && position.y >= tile->pos.y &&
            position.x < tile->pos.x + 4 && position.y < tile->pos.y + 4)
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

int Map_GetCollisionIndex(Map* map, Vector position)
{
    for (int i = map->collisionsCursor - 1; i >= 0; i--)
    {
        Box* box = map->collisions[i];

        if (position.x >= box->pos.x && position.y >= box->pos.y &&
            position.x < box->pos.x + box->size.x && position.y < box->pos.y + box->size.y)
        {
            return i;
        }
    }

    return -1;
}

Vector Map_GetCollisionPosition(Map* map, int index)
{
    return map->collisions[index]->pos;
}

void Map_SwitchFrontTile(Map* map, int index)
{
    map->tiles[index]->front = !map->tiles[index]->front;
}

void Map_Free(Map* map)
{
    for (int i = 0; i < map->tilesCursor; i++)
    {
        free(map->tiles[i]);
    }
    free(map->tiles);

    for (int i = 0; i < map->collisionsCursor; i++)
    {
        free(map->collisions[i]);
    }
    free(map->collisions);

    free(map);
}
