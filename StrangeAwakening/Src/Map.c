#include "Map.h"

Map* Map_Create(int size)
{
    Map* map = calloc(1, sizeof(Map));
    if (!map) return NULL;

    map->tiles = calloc(size, sizeof(Tile*));
    if (!map->tiles) return NULL;

    map->collisions = calloc(size, sizeof(Box*));
    if (!map->collisions) return NULL;

    map->rooms = calloc(size, sizeof(Box*));
    if (!map->rooms) return NULL;

    map->size = size;

    return map;
}

void* Map_ArrayAdd(Map* map, void** arr, int* cursor, size_t size)
{
    if (*cursor == map->size) return NULL;

    arr[*cursor] = calloc(1, size);
    if (!arr[*cursor]) return NULL;

    return arr[(*cursor)++];
}

void Map_AddTile(Map* map, Vector position, Vector selected, bool front)
{
    Tile* tile = Map_ArrayAdd(map, map->tiles, &map->tilesCursor, sizeof(Tile));
    if (!tile) return;

    tile->pos = position;
    tile->sprite = selected;
    tile->front = front;
}

void Map_AddCollision(Map* map, Vector position, Vector size)
{
    Box* collision = Map_ArrayAdd(map, map->collisions, &map->collisionsCursor, sizeof(Box));
    if (!collision) return;

    collision->pos = position;
    collision->size = size;
}

void Map_AddRoom(Map* map, Vector position, Vector size)
{
    Box* room = Map_ArrayAdd(map, map->rooms, &map->roomsCursor, sizeof(Box));
    if (!room) return;

    room->pos = position;
    room->size = size;
}

void Map_ArrayRemove(void** arr, int* cursor, int index)
{
    free(arr[index]);
    arr[index] = NULL;

    for (int i = index; i < *cursor - 1; i++) arr[i] = arr[i + 1];

    arr[--(*cursor)] = NULL;
}

void Map_RemoveTile(Map* map, int index)
{
    Map_ArrayRemove(map->tiles, &map->tilesCursor, index);
}

void Map_RemoveCollision(Map* map, int index)
{
    Map_ArrayRemove(map->collisions, &map->collisionsCursor, index);
}

void Map_RemoveRoom(Map* map, int index)
{
    Map_ArrayRemove(map->rooms, &map->roomsCursor, index);
}

int Map_GetTileIndex(Map* map, Vector position)
{
    for (int i = map->tilesCursor - 1; i >= 0; i--)
    {
        Tile* tile = map->tiles[i];

        if (position.x >= tile->pos.x &&
            position.y >= tile->pos.y &&
            position.x < tile->pos.x + 4 &&
            position.y < tile->pos.y + 4)
        {
            return i;
        }
    }

    return -1;
}

int Map_GetCollisionIndex(Map* map, Vector position)
{
    for (int i = map->collisionsCursor - 1; i >= 0; i--)
    {
        Box* box = map->collisions[i];

        if (position.x >= box->pos.x &&
            position.y >= box->pos.y &&
            position.x < box->pos.x + box->size.x &&
            position.y < box->pos.y + box->size.y)
        {
            return i;
        }
    }

    return -1;
}

int Map_GetRoomIndex(Map* map, Vector position)
{
    for (int i = map->roomsCursor - 1; i >= 0; i--)
    {
        Box* box = map->rooms[i];

        if (position.x >= box->pos.x &&
            position.y >= box->pos.y &&
            position.x < box->pos.x + box->size.x &&
            position.y < box->pos.y + box->size.y)
        {
            return i;
        }
    }

    return -1;
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

    for (int i = 0; i < map->collisionsCursor; i++)
    {
        free(map->collisions[i]);
    }

    for (int i = 0; i < map->roomsCursor; i++)
    {
        free(map->rooms[i]);
    }

    free(map->tiles);
    free(map->collisions);
    free(map->rooms);

    free(map);
}
