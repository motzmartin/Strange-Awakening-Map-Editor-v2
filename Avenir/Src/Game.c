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

    game->collisionSize.x = 1;
    game->collisionSize.y = 1;

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
    }
}

void Game_Update(Game* game, bool* events, Vector mouse, Uint8* keyboard)
{
    Uint64 prevTimer = game->timer;
    game->timer = SDL_GetTicksNS();
    Uint64 elapsed = game->timer - prevTimer;

    if (keyboard[SDL_SCANCODE_E]) game->mode = 1;
    else if (keyboard[SDL_SCANCODE_F]) game->mode = 2;
    else if (keyboard[SDL_SCANCODE_R]) game->mode = 3;
    else if (keyboard[SDL_SCANCODE_C]) game->mode = 4;
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
        default:
            Map_AddTile(game->map, game->cursor, game->selected, false);
        }
    }

    if (events[1]) game->grid = !game->grid;

    if (events[2]) game->collisionSize.x--;
    if (events[3]) game->collisionSize.y--;
    if (events[4]) game->collisionSize.x++;
    if (events[5]) game->collisionSize.y++;

    if (events[6])
    {
        LevelLoader_Save(game->map->tiles,
            game->map->collisions,
            game->map->tilesCursor,
            game->map->collisionsCursor,
            game->player->pos);
    }

    if (events[7])
    {
        LevelLoader_Load(game->map->tiles,
            game->map->collisions,
            &game->map->tilesCursor,
            &game->map->collisionsCursor,
            &game->player->pos);
    }

    game->collisionSize = Vector_Constrain(game->collisionSize, Vector_New(1, 1), Vector_New(256, 256));

    if (game->mode == 0)
    {
        Player_Update(game->player,
            game->map->collisions,
            game->map->collisionsCursor,
            keyboard,
            elapsed);
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
        Camera_GetCentered(game->camera),
        game->cursor,
        game->selected,
        game->collisionSize,
        game->map->tiles,
        game->map->collisions,
        game->map->tilesCursor,
        game->map->collisionsCursor,
        game->tilePointed,
        game->collisionPointed,
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
