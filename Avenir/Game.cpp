#include "Game.h"

void Game::Update(bool* events, Uint8* keyboard, int mouseX, int mouseY)
{
    hud.Update(mouseX, mouseY, events[1]);
    grid.Update(hud.GetSelectedX(), hud.GetSelectedY(), events[0], events[2]);
}

Hud* Game::GetHud() { return &hud; }

Grid* Game::GetGrid() { return &grid; }
