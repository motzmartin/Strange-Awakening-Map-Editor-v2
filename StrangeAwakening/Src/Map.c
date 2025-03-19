#include "Map.h"

Map* Map_Create(int size)
{
    Map* map = calloc(1, sizeof(Map));
    if (!map) return NULL;

    map->tiles = DynamicArray_Create(size, sizeof(Tile));
    if (!map->tiles) return NULL;

    for (int i = 0; i < TYPES_NUMBER; i++)
    {
        map->boxes[i] = DynamicArray_Create(size, sizeof(Box));
        if (!map->boxes[i]) return NULL;
    }

    return map;
}

void Map_AddTile(Map* map, Vector pos, Vector selected, bool front)
{
    Tile* tile = DynamicArray_Add(map->tiles);
    if (!tile) return;

    tile->pos = pos;
    tile->sprite = selected;
    tile->front = front;
}

void Map_AddBox(Map* map, BoxType type, Vector pos, Vector size)
{
    Box* box = DynamicArray_Add(map->boxes[type]);
    if (!box) return;

    box->pos = pos;
    box->size = size;
}

void Map_RemoveTile(Map* map, int index)
{
    DynamicArray_Remove(map->tiles, index);
}

void Map_RemoveBox(Map* map, BoxType type, int index)
{
    DynamicArray_Remove(map->boxes[type], index);
}

int Map_GetTileIndexByPos(Map* map, Vector pos)
{
    for (int i = DynamicArray_GetSize(map->tiles) - 1; i >= 0; i--)
    {
        Tile* tile = DynamicArray_Get(map->tiles, i);

        if (pos.x >= tile->pos.x &&
            pos.y >= tile->pos.y &&
            pos.x < tile->pos.x + 4 &&
            pos.y < tile->pos.y + 4)
        {
            return i;
        }
    }

    return -1;
}

int Map_GetBoxIndexByPos(Map* map, BoxType type, Vector pos)
{
    for (int i = DynamicArray_GetSize(map->boxes[type]) - 1; i >= 0; i--)
    {
        Box* box = DynamicArray_Get(map->boxes[type], i);

        if (pos.x >= box->pos.x &&
            pos.y >= box->pos.y &&
            pos.x < box->pos.x + box->size.x &&
            pos.y < box->pos.y + box->size.y)
        {
            return i;
        }
    }

    return -1;
}

void Map_Clear(Map* map)
{
    DynamicArray_Clear(map->tiles);

    for (int i = 0; i < TYPES_NUMBER; i++)
    {
        DynamicArray_Clear(map->boxes[i]);
    }
}

void Map_SwitchFrontTile(Map* map, int index)
{
    Tile* tile = DynamicArray_Get(map->tiles, index);

    tile->front = !tile->front;
}

void Map_Free(Map* map)
{
    for (int i = 0; i < TYPES_NUMBER; i++)
    {
        DynamicArray_Free(map->boxes[i]);
    }

    DynamicArray_Free(map->tiles);

    free(map);
}
