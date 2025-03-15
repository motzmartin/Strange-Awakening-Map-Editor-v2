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

    map->lights = calloc(size, sizeof(Light*));
    if (!map->lights) return NULL;

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

void Map_AddLight(Map* map, Vector position, Vector size, bool emit)
{
    Light* light = Map_ArrayAdd(map, map->lights, &map->lightsCursor, sizeof(Light));
    if (!light) return;

    light->pos = position;
    light->size = size;
    light->emit = emit;
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

void Map_RemoveLight(Map* map, int index)
{
    Map_ArrayRemove(map->lights, &map->lightsCursor, index);
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

int Map_GetLightIndex(Map* map, Vector position)
{
    for (int i = map->lightsCursor - 1; i >= 0; i--)
    {
        Light* light = map->lights[i];

        if (position.x >= light->pos.x &&
            position.y >= light->pos.y &&
            position.x < light->pos.x + light->size.x &&
            position.y < light->pos.y + light->size.y)
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

    if (map->lightsTexture)
    {
        SDL_DestroyTexture(map->lightsTexture);
    }

    free(map);
}

void Map_ProcessLights(Map* map, SDL_Renderer* renderer)
{
    if (map->lightsTexture)
    {
        SDL_DestroyTexture(map->lightsTexture);
        map->lightsTexture = NULL;
    }

    if (!map->lightsCursor)
    {
        return;
    }

    Vector min = map->lights[0]->pos;
    Vector max = map->lights[0]->pos;

    for (int i = 0; i < map->lightsCursor; i++)
    {
        Light* light = map->lights[i];

        if (light->pos.x < min.x) min.x = light->pos.x;
        if (light->pos.y < min.y) min.y = light->pos.y;

        if (light->pos.x + light->size.x > max.x) max.x = light->pos.x + light->size.x;
        if (light->pos.y + light->size.y > max.y) max.y = light->pos.y + light->size.y;
    }

    map->lightsPos = min;

    Vector size = Vector_Sub(max, min);

    map->lightsSize = size;

    // LIGHTS ALLOCATION

    float** lights = calloc(size.y * 2, sizeof(float*));
    if (!lights) return;

    for (int i = 0; i < size.y * 2; i++)
    {
        lights[i] = calloc(size.x * 2, sizeof(float));
        if (!lights[i]) return;
    }

    float intensity = 1.0f;

    for (int i = 0; i < map->lightsCursor; i++)
    {
        Light* light = map->lights[i];

        if (light->emit)
        {
            for (int j = 0; j < light->size.y; j++)
            {
                for (int k = 0; k < light->size.x; k++)
                {
                    lights[(j + light->pos.y - min.y) * 2][(k + light->pos.x - min.x) * 2] = intensity;
                    lights[(j + light->pos.y - min.y) * 2][(k + light->pos.x - min.x) * 2 + 1] = intensity;
                    lights[(j + light->pos.y - min.y) * 2 + 1][(k + light->pos.x - min.x) * 2] = intensity;
                    lights[(j + light->pos.y - min.y) * 2 + 1][(k + light->pos.x - min.x) * 2 + 1] = intensity;
                }
            }
        }
    }

    intensity -= 0.01f;

    // LIGHTS PROCESS

    while (intensity > 0.f)
    {
        float** temp = calloc(size.y * 2, sizeof(float*));
        if (!temp) return;

        for (int i = 0; i < size.y * 2; i++)
        {
            temp[i] = calloc(size.x * 2, sizeof(float));
            if (!temp[i]) return;

            for (int j = 0; j < size.x * 2; j++)
            {
                temp[i][j] = lights[i][j];
            }
        }

        for (int i = 0; i < size.y * 2; i++)
        {
            for (int j = 0; j < size.x * 2; j++)
            {
                int lightIndex = Map_GetLightIndex(map, Vector_New(min.x + j / 2, min.y + i / 2));

                if (temp[i][j] == 0 && lightIndex != -1)
                {
                    if ((j > 0 && temp[i][j - 1] > 0) ||
                        (i > 0 && temp[i - 1][j] > 0) ||
                        (j < size.x * 2 - 1 && temp[i][j + 1] > 0) ||
                        (i < size.y * 2 - 1 && temp[i + 1][j] > 0))
                    {
                        lights[i][j] = intensity;
                    }
                }
            }
        }

        intensity -= 0.01f;

        for (int i = 0; i < size.y * 2; i++)
        {
            free(temp[i]);
        }

        free(temp);
    }

    // TEXTURE CREATION

    map->lightsTexture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        size.x * 2,
        size.y * 2);
    if (!map->lightsTexture) return;

    SDL_SetTextureScaleMode(map->lightsTexture, SDL_SCALEMODE_NEAREST);

    const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);

    Uint32* pixels = NULL;
    int pitch = 0;

    SDL_LockTexture(map->lightsTexture, NULL, &pixels, &pitch);

    for (int i = 0; i < size.y * 2; i++)
    {
        for (int j = 0; j < size.x * 2; j++)
        {
            pixels[i * size.x * 2 + j] = SDL_MapRGBA(format, NULL, 0, 0, 0, 255 - (Uint8)(lights[i][j] * 255.f));
        }
    }

    SDL_UnlockTexture(map->lightsTexture);

    for (int i = 0; i < size.y * 2; i++)
    {
        free(lights[i]);
    }

    free(lights);
}
