#include "Game.h"

Game::Game()
{
    hud = std::make_unique<Hud>();
    map = std::make_unique<Map>();
}

void Game::Update(bool* events, int mouseX, int mouseY, Uint8* keyboard)
{
    hud->Update(mouseX, mouseY, keyboard[SDL_SCANCODE_E]);

    map->Update(hud->GetHoveredX(),
        hud->GetHoveredY(),
        hud->GetTileSelectedX(),
        hud->GetTileSelectedY(),
        events[0]);
}

void Game::Draw(SDL_Renderer* renderer, SDL_Texture** textures)
{
    map->Draw(renderer, textures[0]);
    hud->Draw(renderer, textures[0]);
}
