#include "Game.h"

void Game::SetPointed(SDL_FPoint mouse)
{
    if (mode == 1)
    {
        pointed.x = floorf(mouse.x / 16.f);
        pointed.y = floorf(mouse.y / 16.f);

        if (pointed.x < 16.f) pointed.x = 16.f;
        else if (pointed.x > 23.f) pointed.x = 23.f;

        if (pointed.y < 8.f) pointed.y = 8.f;
        else if (pointed.y > 15.f) pointed.y = 15.f;
    }
    else if (mode == 2 || mode == 3)
    {
        tileSelected = map->GetTile({ floorf(mouse.x / 4.f), floorf(mouse.y / 4.f) }, &pointed);
    }
    else
    {
        pointed.x = floorf(mouse.x / 4.f);
        pointed.y = floorf(mouse.y / 4.f);
    }
}

Game::Game()
{
    hud = std::make_unique<Hud>();
    map = std::make_unique<Map>();
    player = std::make_unique<Player>();
}

void Game::Update(bool* events, SDL_FPoint mouse, Uint8* keyboard)
{
    int prevMode = mode;

    if (keyboard[SDL_SCANCODE_E]) mode = 1;
    else if (keyboard[SDL_SCANCODE_F]) mode = 2;
    else if (keyboard[SDL_SCANCODE_R]) mode = 3;
    else mode = 0;

    if (mode != prevMode)
    {
        if (prevMode == 1)
        {
            selected.x = pointed.x - 16.f;
            selected.y = pointed.y - 8.f;
        }
        else if (prevMode == 2)
        {
            if (tileSelected != -1) map->SwitchFrontTile(tileSelected);
        }
        else if (prevMode == 3)
        {
            if (tileSelected != -1) map->RemoveTile(tileSelected);
        }
    }

    SetPointed({ floorf(mouse.x / 2.f), floorf(mouse.y / 2.f) });

    if (events[1]) grid = (grid + 1) % 3;
    if (events[0]) map->AddTile(pointed, selected, false);

    player->Update(keyboard);
}

void Game::Draw(SDL_Renderer* renderer, SDL_Texture** textures)
{
    map->Draw(renderer, textures[0], true, player->GetY());
    player->Draw(renderer);
    map->Draw(renderer, textures[0], false, player->GetY());

    std::vector<SDL_FPoint> frontTiles;
    if (mode == 2) map->GetFrontTiles(&frontTiles);

    hud->Draw(renderer, textures[0], pointed, selected, &frontTiles, mode, grid, tileSelected != -1);
}
