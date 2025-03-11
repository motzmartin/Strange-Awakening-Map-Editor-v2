#include "Game.h"

Game::Game()
{
    hud = std::make_unique<Hud>();
    grid = std::make_unique<Grid>();
}

void Game::Update(bool* events, int mouseX, int mouseY)
{
    hud->Update(mouseX, mouseY, events[1]);
    grid->Update(hud->GetSelectedX(), hud->GetSelectedY(), events[0], events[2]);
}

Hud* Game::GetHud()
{
    return hud.get();
}

Grid* Game::GetGrid()
{
    return grid.get();
}
