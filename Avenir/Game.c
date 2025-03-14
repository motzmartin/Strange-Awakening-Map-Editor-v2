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

    game->timer = SDL_GetTicksNS();

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

        if (game->mode == 2 || game->mode == 3)
        {
            game->tilePointed = Map_GetTileIndex(game->map, cursorPos);

            if (game->tilePointed != -1)
            {
                game->cursor = Map_GetTilePosition(game->map, game->tilePointed);
            }
        }
        else
        {
            game->cursor = cursorPos;
        }
    }
}

void Game_Update(Game* game, bool* events, Vector mouse, Uint8* keyboard)
{
    Uint64 prevTimer = game->timer;
    game->timer = SDL_GetTicksNS();
    Uint64 elapsed = game->timer - prevTimer;

    int prevMode = game->mode;

    if (keyboard[SDL_SCANCODE_E]) game->mode = 1;
    else if (keyboard[SDL_SCANCODE_F]) game->mode = 2;
    else if (keyboard[SDL_SCANCODE_R]) game->mode = 3;
    else game->mode = 0;

    if (game->mode != prevMode)
    {
        if (prevMode == 1)
        {
            game->selected = game->cursor;
        }
        else if (prevMode == 2 && game->tilePointed != -1)
        {
            Map_SwitchFrontTile(game->map, game->tilePointed);
        }
        else if (prevMode == 3 && game->tilePointed != -1)
        {
            Map_RemoveTile(game->map, game->tilePointed);
        }
    }

    Game_UpdateCursor(game, mouse);

    if (events[0])
    {
        Map_AddTile(game->map, game->cursor, game->selected, false);
    }

    if (events[1])
    {
        game->grid = !game->grid;
    }

    if (game->mode == 0)
    {
        Player_Update(game->player, keyboard, elapsed);
        Camera_Update(game->camera, game->player->pos, elapsed);
    }
}

void Game_Draw(Game* game, SDL_Renderer* renderer, SDL_Texture** textures)
{
    MapRender_Draw(game->map,
        renderer,
        textures[0],
        Camera_GetCentered(game->camera),
        game->player->pos.y,
        true);

    PlayerRender_Draw(game->player,
        renderer,
        textures[1],
        Camera_GetCentered(game->camera));

    MapRender_Draw(game->map,
        renderer,
        textures[0],
        Camera_GetCentered(game->camera),
        game->player->pos.y,
        false);

    HudRender_Draw(renderer,
        textures[0],
        game->cursor,
        game->selected,
        Camera_GetCentered(game->camera),
        game->mode,
        game->grid,
        game->tilePointed != -1);

    if (game->mode == 2)
    {
        int frontTilesNumber = 0;
        Vector* frontTiles = Map_GetFrontTiles(game->map, &frontTilesNumber);

        HudRender_DrawFrontTiles(renderer,
            game->cursor,
            Camera_GetCentered(game->camera),
            frontTiles,
            frontTilesNumber,
            game->tilePointed != -1);

        Map_FreeFrontTiles(frontTiles);
    }
}

void Game_Free(Game* game)
{
    Camera_Free(game->camera);
    Player_Free(game->player);
    Map_Free(game->map);

    free(game);
}
