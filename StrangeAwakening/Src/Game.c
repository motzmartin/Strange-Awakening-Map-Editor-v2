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

    game->collisionSize.x = 1;
    game->collisionSize.y = 1;

    game->roomSize.x = 4;
    game->roomSize.y = 4;

    game->lightSize.x = 1;
    game->lightSize.y = 1;

    game->counter = SDL_GetPerformanceCounter();

    return game;
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
            game->tilePointed = Map_GetTileIndex(game->map, cursorPos);
        }
        else if (game->mode == 4)
        {
            game->collisionPointed = Map_GetCollisionIndex(game->map, cursorPos);
        }
        else if (game->mode == 5)
        {
            game->roomPointed = Map_GetRoomIndex(game->map, cursorPos);
        }
        else if (game->mode == 6)
        {
            game->lightPointed = Map_GetLightIndex(game->map, cursorPos);
        }
    }
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
    else game->mode = 0;

    Game_UpdateCursor(game, mouse);

    if (events[0])
    {
        switch (game->mode)
        {
        case 1:
            game->selected = game->cursor;
            break;
        case 2:
            if (game->tilePointed != -1)
            {
                Map_SwitchFrontTile(game->map, game->tilePointed);
            }
            break;
        case 3:
            if (game->tilePointed != -1)
            {
                Map_RemoveTile(game->map, game->tilePointed);
                game->tilePointed = -1;
            }
            break;
        case 4:
            if (game->collisionPointed != -1)
            {
                Map_RemoveCollision(game->map, game->collisionPointed);
                game->collisionPointed = -1;
            }
            else
            {
                Map_AddCollision(game->map, game->cursor, game->collisionSize);
            }
            break;
        case 5:
            if (game->roomPointed != -1)
            {
                Map_RemoveRoom(game->map, game->roomPointed);
                game->roomPointed = -1;
            }
            else
            {
                Map_AddRoom(game->map, game->cursor, game->roomSize);
            }
            break;
        case 6:
            if (game->lightPointed != -1)
            {
                Map_RemoveLight(game->map, game->lightPointed);
                game->lightPointed = -1;
            }
            else
            {
                Map_AddLight(game->map, game->cursor, game->lightSize, false);
            }

            Map_ProcessLights(game->map, renderer);
            break;
        default:
            Map_AddTile(game->map, game->cursor, game->selected, false);
        }
    }

    if (events[1])
    {
        if (game->mode == 6)
        {
            Map_AddLight(game->map, game->cursor, game->lightSize, true);
            Map_ProcessLights(game->map, renderer);
        }
    }

    if (events[2])
    {
        if (game->mode == 4) game->collisionSize.x--;
        else if (game->mode == 5) game->roomSize.x--;
        else if (game->mode == 6) game->lightSize.x--;
    }
    else if (events[3])
    {
        if (game->mode == 4) game->collisionSize.y--;
        else if (game->mode == 5) game->roomSize.y--;
        else if (game->mode == 6) game->lightSize.y--;
    }
    else if (events[4])
    {
        if (game->mode == 4) game->collisionSize.x++;
        else if (game->mode == 5) game->roomSize.x++;
        else if (game->mode == 6) game->lightSize.x++;
    }
    else if (events[5])
    {
        if (game->mode == 4) game->collisionSize.y++;
        else if (game->mode == 5) game->roomSize.y++;
        else if (game->mode == 6) game->lightSize.y++;
    }

    game->collisionSize = Vector_Constrain(game->collisionSize, Vector_New(1, 1), Vector_New(256, 256));
    game->roomSize = Vector_Constrain(game->roomSize, Vector_New(1, 1), Vector_New(256, 256));
    game->lightSize = Vector_Constrain(game->lightSize, Vector_New(1, 1), Vector_New(256, 256));

    if (events[6]) game->grid = !game->grid;

    if (events[7])
    {
        LevelLoader_Save(game->player->pos,
            game->map->tiles,
            game->map->collisions,
            game->map->rooms,
            game->map->lights,
            game->map->tilesCursor,
            game->map->collisionsCursor,
            game->map->roomsCursor,
            game->map->lightsCursor);
    }

    if (events[8])
    {
        LevelLoader_Load(&game->player->pos,
            game->map->tiles,
            game->map->collisions,
            game->map->rooms,
            game->map->lights,
            &game->map->tilesCursor,
            &game->map->collisionsCursor,
            &game->map->roomsCursor,
            &game->map->lightsCursor);

        Map_ProcessLights(game->map, renderer);
    }

    if (game->mode == 0)
    {
        Player_Update(game->player,
            keyboard,
            game->map->collisions,
            game->map->collisionsCursor,
            elapsed);

        Camera_Update(game->camera,
            game->player->pos,
            game->map->rooms,
            game->map->roomsCursor,
            elapsed);
    }
}

void Game_Draw(Game* game, SDL_Renderer* renderer, SDL_Texture** textures)
{
    Vector cameraCentered = Camera_GetCentered(game->camera);

    MapRender_Draw(game->map,
        renderer,
        textures[0],
        cameraCentered,
        game->player->pos.y,
        true);

    PlayerRender_Draw(game->player,
        renderer,
        textures[1],
        cameraCentered);

    MapRender_Draw(game->map,
        renderer,
        textures[0],
        cameraCentered,
        game->player->pos.y,
        false);

    MapRender_DrawLights(game->map, renderer, cameraCentered);

    HudRender_Draw(renderer,
        textures[0],
        cameraCentered,
        game->cursor,
        game->selected,
        game->collisionSize,
        game->roomSize,
        game->lightSize,
        game->map->tiles,
        game->map->collisions,
        game->map->rooms,
        game->map->lights,
        game->map->tilesCursor,
        game->map->collisionsCursor,
        game->map->roomsCursor,
        game->map->lightsCursor,
        game->tilePointed,
        game->collisionPointed,
        game->roomPointed,
        game->lightPointed,
        game->mode,
        game->grid);
}

void Game_Free(Game* game)
{
    Camera_Free(game->camera);
    Player_Free(game->player);
    Map_Free(game->map);

    free(game);
}
