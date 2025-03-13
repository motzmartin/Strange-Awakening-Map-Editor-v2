#include "Game.h"

Game* Game_Create()
{
    Game* game = calloc(1, sizeof(Game));
    if (!game) return NULL;

    game->map = Map_Create();
    if (!game->map) return NULL;

    game->player = Player_Create();
    if (!game->player) return NULL;

    return game;
}

void Game_SetPointed(Game* game, Position mouse)
{
    if (game->mode == 1)
    {
        game->pointed.x = floorf(mouse.x / 16.f);
        game->pointed.y = floorf(mouse.y / 16.f);

        if (game->pointed.x < 16.f) game->pointed.x = 16.f;
        else if (game->pointed.x > 23.f) game->pointed.x = 23.f;

        if (game->pointed.y < 8.f) game->pointed.y = 8.f;
        else if (game->pointed.y > 15.f) game->pointed.y = 15.f;
    }
    else if (game->mode == 2 || game->mode == 3)
    {
        Position pos = { floorf(mouse.x / 4.f), floorf(mouse.y / 4.f) };
        game->tileSelected = Map_GetTile(game->map, pos, &game->pointed);
    }
    else
    {
        game->pointed.x = floorf(mouse.x / 4.f);
        game->pointed.y = floorf(mouse.y / 4.f);
    }
}

void Game_Update(Game* game, bool* events, Position mouse, Uint8* keyboard)
{
    int prevMode = game->mode;

    if (keyboard[SDL_SCANCODE_E]) game->mode = 1;
    else if (keyboard[SDL_SCANCODE_F]) game->mode = 2;
    else if (keyboard[SDL_SCANCODE_R]) game->mode = 3;
    else game->mode = 0;

    if (game->mode != prevMode)
    {
        if (prevMode == 1)
        {
            game->selected.x = game->pointed.x - 16.f;
            game->selected.y = game->pointed.y - 8.f;
        }
        else if (prevMode == 2)
        {
            if (game->tileSelected != -1) Map_SwitchFrontTile(game->map, game->tileSelected);
        }
        else if (prevMode == 3)
        {
            if (game->tileSelected != -1) Map_RemoveTile(game->map, game->tileSelected);
        }
    }

    Position pos = { floorf(mouse.x / 2.f), floorf(mouse.y / 2.f) };
    Game_SetPointed(game, pos);

    if (events[1]) game->grid = (game->grid + 1) % 3;
    if (events[0]) Map_AddTile(game->map, game->pointed, game->selected, false);

    Player_Update(game->player, keyboard);
}

void Game_Draw(Game* game, SDL_Renderer* renderer, SDL_Texture** textures)
{
    MapRender_Draw(game->map, renderer, textures[0], true, game->player->pos.y);
    PlayerRender_Draw(game->player, renderer);
    MapRender_Draw(game->map, renderer, textures[0], false, game->player->pos.y);

    HudRender_Draw(renderer,
        textures[0],
        game->pointed,
        game->selected,
        game->mode,
        game->grid,
        game->tileSelected != -1);

    if (game->mode == 2)
    {
        Position** frontTiles = Map_GetFrontTiles(game->map);

        HudRender_DrawFrontTiles(renderer, frontTiles, game->pointed, game->tileSelected != -1);

        Map_FreeFrontTiles(frontTiles);
    }
}

void Game_Free(Game* game)
{
    Player_Free(game->player);
    Map_Free(game->map);

    free(game);
}
