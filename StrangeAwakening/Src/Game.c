#include "Game.h"

Game* Game_Create()
{
    Game* game = calloc(1, sizeof(Game));
    if (!game) return NULL;

    game->map = Map_Create(4096);
    if (!game->map) return NULL;

    game->player = Player_Create();
    if (!game->player) return NULL;

    game->camera = Camera_Create();
    if (!game->camera) return NULL;

    game->lights = Lights_Create(2);
    if (!game->lights) return NULL;

    for (int i = 0; i < SIZE; i++)
    {
        game->sizes[i].x = 1;
        game->sizes[i].y = 1;
    }

    game->counter = SDL_GetPerformanceCounter();

    return game;
}

void Game_Update(Game* game, SDL_Renderer* renderer, bool* events, Vector mouse, Uint8* keyboard)
{
    Uint64 now = SDL_GetPerformanceCounter();
    float elapsed = (float)(now - game->counter) / (float)SDL_GetPerformanceFrequency();
    game->counter = now;

    if (keyboard[SDL_SCANCODE_E]) game->mode = 1;
    else if (keyboard[SDL_SCANCODE_F]) game->mode = 2;
    else if (keyboard[SDL_SCANCODE_R]) game->mode = 3;
    else if (keyboard[SDL_SCANCODE_C]) game->mode = 4;
    else if (keyboard[SDL_SCANCODE_T]) game->mode = 5;
    else if (keyboard[SDL_SCANCODE_I]) game->mode = 6;
    else if (keyboard[SDL_SCANCODE_O]) game->mode = 7;
    else game->mode = 0;

    Game_UpdateCursor(game, mouse);

    if (events[0])
    {
        if (game->mode == 0)
        {
            Map_AddTile(game->map, game->cursor, game->selected, false);
        }
        else if (game->mode == 1)
        {
            game->selected = game->cursor;
        }
        else if (game->mode == 2)
        {
            if (game->pointed != -1)
            {
                Map_SwitchFrontTile(game->map, game->pointed);
            }
        }
        else if (game->mode == 3)
        {
            if (game->pointed != -1)
            {
                Map_RemoveTile(game->map, game->pointed);
                game->pointed = -1;
            }
        }
        else if (game->mode >= 4 && game->mode <= 7)
        {
            BoxType type = game->mode - 4;

            if (game->pointed != -1)
            {
                Map_RemoveBox(game->map, type, game->pointed);
                game->pointed = -1;
            }
            else
            {
                Map_AddBox(game->map, type, game->cursor, game->sizes[type]);
            }
        }
    }

    if (game->mode >= 4 && game->mode <= 7)
    {
        BoxType type = game->mode - 4;

        if (events[2]) game->sizes[type].x--;
        else if (events[3]) game->sizes[type].y--;
        else if (events[4]) game->sizes[type].x++;
        else if (events[5]) game->sizes[type].y++;

        game->sizes[type] = Vector_Constrain(game->sizes[type], Vector_New(1, 1), Vector_New(256, 256));
    }

    if (events[6]) game->grid = !game->grid;
    if (events[7]) LevelLoader_Save(game->player->pos, game->map->tiles, game->map->boxes);
    if (events[8]) LevelLoader_Load(&game->player->pos, game->map->tiles, game->map->boxes);
    if (events[8] || events[9]) Lights_Process(game->lights, game->map->boxes, renderer);

    if (game->mode == 0)
    {
        Player_Update(game->player, keyboard, game->map->boxes[COLLISIONS], elapsed);
        Camera_Update(game->camera, game->player->pos, game->map->boxes[ROOMS], elapsed);
    }
}

void Game_UpdateCursor(Game* game, Vector mouse)
{
    if (game->mode == 1)
    {
        Vector min = Vector_New(0, 0);
        Vector max = Vector_New(7, 7);

        Vector cursorPos = Vector_Sub(Vector_Div(mouse, 48), Vector_New(8, 4));
        game->cursor = Vector_Constrain(cursorPos, min, max);
    }
    else
    {
        Vector cursorPos = Vector_Div(Vector_Add(mouse, Camera_GetCentered(game->camera)), 12);
        game->cursor = cursorPos;

        if (game->mode == 2 || game->mode == 3)
        {
            game->pointed = Map_GetTileIndexByPos(game->map, cursorPos);
        }
        else if (game->mode >= 4 && game->mode <= 7)
        {
            game->pointed = Map_GetBoxIndexByPos(game->map, game->mode - 4, cursorPos);
        }
    }
}

void Game_Draw(Game* game, SDL_Renderer* renderer, DynamicArray* textures)
{
    Vector cameraCentered = Camera_GetCentered(game->camera);

    MapRender_Draw(game->map,
        renderer,
        *(SDL_Texture**)DynamicArray_Get(textures, 0),
        cameraCentered,
        game->player->pos.y,
        true);

    PlayerRender_Draw(game->player,
        renderer,
        *(SDL_Texture**)DynamicArray_Get(textures, 1),
        cameraCentered);

    MapRender_Draw(game->map,
        renderer,
        *(SDL_Texture**)DynamicArray_Get(textures, 0),
        cameraCentered,
        game->player->pos.y,
        false);

    LightsRender_Draw(game->lights, renderer, cameraCentered);

    HudRender_Draw(renderer,
        *(SDL_Texture**)DynamicArray_Get(textures, 0),
        cameraCentered,
        game->cursor,
        game->selected,
        game->map->tiles,
        game->map->boxes,
        game->sizes,
        game->pointed,
        game->mode,
        game->grid);
}

void Game_Free(Game* game)
{
    Lights_Free(game->lights);
    Camera_Free(game->camera);
    Player_Free(game->player);
    Map_Free(game->map);

    free(game);
}
