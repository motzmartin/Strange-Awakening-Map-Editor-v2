#include "Game.h"

void Game::SetPointed(int mouseX, int mouseY)
{
    if (menu == 1)
    {
        pointedX = mouseX / 32;
        pointedY = mouseY / 32;

        if (pointedX < 16) pointedX = 16;
        else if (pointedX > 23) pointedX = 23;

        if (pointedY < 8) pointedY = 8;
        else if (pointedY > 15) pointedY = 15;
    }
    else if (menu == 2)
    {
        tileSelected = map->GetTile(mouseX / 8, mouseY / 8, &pointedX, &pointedY);
    }
    else
    {
        pointedX = (mouseX - 12) / 8;
        pointedY = (mouseY - 12) / 8;
    }
}

Game::Game()
{
    hud = std::make_unique<Hud>();
    map = std::make_unique<Map>();
    player = std::make_unique<Player>();
}

void Game::Update(bool* events, int mouseX, int mouseY, Uint8* keyboard)
{
    int prevMenu = menu;

    if (keyboard[SDL_SCANCODE_E])
    {
        menu = 1;
    }
    else if (keyboard[SDL_SCANCODE_F])
    {
        menu = 2;
    }
    else
    {
        menu = 0;
    }

    if (menu != prevMenu)
    {
        if (prevMenu == 1)
        {
            selectedX = pointedX - 16;
            selectedY = pointedY - 8;
        }
        else if (prevMenu == 2)
        {
            if (tileSelected != -1)
            {
                map->SwitchFrontTile(tileSelected);
            }
        }
    }

    SetPointed(mouseX, mouseY);

    player->Update(keyboard);

    if (menu == 0)
    {
        map->Update(pointedX, pointedY, selectedX, selectedY, events[0]);
    }
}

void Game::Draw(SDL_Renderer* renderer, SDL_Texture** textures)
{
    map->Draw(renderer, textures[0], true, player->GetY());
    player->Draw(renderer);
    map->Draw(renderer, textures[0], false, player->GetY());

    std::vector<SDL_Point> frontTiles;

    if (menu == 2)
    {
        map->GetFrontTiles(&frontTiles);
    }

    hud->Draw(renderer,
        textures[0],
        menu,
        pointedX,
        pointedY,
        selectedX,
        selectedY,
        &frontTiles,
        tileSelected != -1);
}
