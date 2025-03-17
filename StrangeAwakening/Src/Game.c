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

    game->size = Vector_New(1, 1);

    game->pointed = -1;
    game->modeSelected = -1;

    game->counter = SDL_GetPerformanceCounter();

    return game;
}

void Game_Update(Game* game, SDL_Renderer* renderer, bool* events, Vector mouse, Uint8* keyboard)
{
    Uint64 now = SDL_GetPerformanceCounter();
    float elapsed = (float)(now - game->counter) / (float)SDL_GetPerformanceFrequency();
    game->counter = now;

    game->showInventory = game->mode == 0 && keyboard[SDL_SCANCODE_E];

    Game_UpdateCursor(game, mouse);

    if (events[0])
    {
        if (game->modeSelected != -1)
        {
            game->mode = game->modeSelected;

            game->resizeActive = false;
            game->size = Vector_New(1, 1);
        }
        else if (game->showInventory)
        {
            game->selected = game->cursor;
        }
        else if (game->mode == 0)
        {
            Map_AddTile(game->map, game->cursor, game->selected, false);
        }
        else if (game->mode == 1)
        {
            if (game->pointed != -1)
            {
                Map_RemoveTile(game->map, game->pointed);
                game->pointed = -1;
            }
        }
        else if (game->mode == 2)
        {
            if (game->pointed != -1)
            {
                Map_SwitchFrontTile(game->map, game->pointed);
            }
        }
        else if (game->mode >= 3 && game->mode <= 6)
        {
            if (game->pointed != -1)
            {
                Map_RemoveBox(game->map, game->mode - 3, game->pointed);
                game->pointed = -1;
            }
            else
            {
                game->resizeActive = true;
            }
        }
    }

    if (events[1] && game->resizeActive)
    {
        Map_AddBox(game->map, game->mode - 3, game->cursor, game->size);

        game->resizeActive = false;
        game->size = Vector_New(1, 1);
    }

    if (events[6]) game->grid = !game->grid;
    if (events[7]) LevelLoader_Save(game->player->pos, game->map->tiles, game->map->boxes);
    if (events[8]) LevelLoader_Load(&game->player->pos, game->map->tiles, game->map->boxes);
    if (events[8] || events[9]) Lights_Process(game->lights, game->map->boxes, renderer);

    Player_Update(game->player, keyboard, game->map->boxes[COLLISIONS], elapsed);
    Camera_Update(game->camera, game->player->pos, game->map->boxes[ROOMS], elapsed);
}

void Game_UpdateCursor(Game* game, Vector mouse)
{
    for (int i = 0; i < 8; i++)
    {
        Vector pos = Vector_New(i * 30 + 6, 768 - 30 - 6);

        if (mouse.x >= pos.x && mouse.x < pos.x + 30 && mouse.y >= pos.y && mouse.y < pos.y + 30)
        {
            game->modeSelected = i;
            return;
        }
    }

    game->modeSelected = -1;

    if (game->showInventory)
    {
        Vector min = Vector_New(0, 0);
        Vector max = Vector_New(7, 7);

        Vector cursorPos = Vector_Sub(Vector_Div(mouse, 48), Vector_New(8, 4));
        game->cursor = Vector_Constrain(cursorPos, min, max);
    }
    else
    {
        Vector cursorPos = Vector_Div(Vector_Add(mouse, Camera_GetCentered(game->camera)), 12);

        if (game->resizeActive)
        {
            if (game->mode >= 3 && game->mode <= 6)
            {
                Vector size = Vector_Add(Vector_Sub(cursorPos, game->cursor), Vector_New(1, 1));
                game->size = Vector_Constrain(size, Vector_New(1, 1), Vector_New(256, 256));
            }
        }
        else
        {
            game->cursor = cursorPos;

            if (game->mode == 1 || game->mode == 2)
            {
                game->pointed = Map_GetTileIndexByPos(game->map, cursorPos);
            }
            else if (game->mode >= 3 && game->mode <= 6)
            {
                game->pointed = Map_GetBoxIndexByPos(game->map, game->mode - 3, cursorPos);
            }
        }
    }
}

void Game_Draw(Game* game, SDL_Renderer* renderer, DynamicArray* textures)
{
    Vector cameraCentered = Camera_GetCentered(game->camera);

    MapRender_Draw(game->map,
        renderer,
        TextureLoader_Get(textures, 0),
        cameraCentered,
        game->player->pos.y,
        true);

    PlayerRender_Draw(game->player,
        renderer,
        TextureLoader_Get(textures, 1),
        cameraCentered);

    MapRender_Draw(game->map,
        renderer,
        TextureLoader_Get(textures, 0),
        cameraCentered,
        game->player->pos.y,
        false);

    LightsRender_Draw(game->lights, renderer, cameraCentered);

    HudRender_Draw(renderer,
        TextureLoader_Get(textures, 0),
        TextureLoader_Get(textures, 2),
        cameraCentered,
        game->cursor,
        game->selected,
        game->map->tiles,
        game->map->boxes,
        game->size,
        game->pointed,
        game->mode,
        game->modeSelected,
        game->showInventory,
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
