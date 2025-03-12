#pragma once

#include <vector>
#include <SDL3/SDL.h>

class Hud
{
private:
    void DrawInventory(SDL_Renderer* renderer,
        SDL_Texture* sprites,
        int pointedX,
        int pointedY,
        int selectedX,
        int selectedY);
    void DrawFrontTiles(SDL_Renderer* renderer,
        std::vector<SDL_Point>* frontTiles,
        int pointedX,
        int pointedY);

public:
    void Draw(SDL_Renderer* renderer,
        SDL_Texture* sprites,
        int menu,
        int pointedX,
        int pointedY,
        int selectedX,
        int selectedY,
        std::vector<SDL_Point>* frontTiles,
        bool isTileSelected);
};
