#pragma once

#include <vector>
#include <SDL3/SDL.h>

class Hud
{
private:
    void DrawInventory(SDL_Renderer* renderer,
        SDL_Texture* sprites,
        SDL_FPoint pointed,
        SDL_FPoint selected);
    void DrawFrontTiles(SDL_Renderer* renderer,
        std::vector<SDL_FPoint>* frontTiles,
        SDL_FPoint pointed,
        bool isTileSelected);

public:
    void Draw(SDL_Renderer* renderer,
        SDL_Texture* sprites,
        SDL_FPoint pointed,
        SDL_FPoint selected,
        std::vector<SDL_FPoint>* frontTiles,
        int mode,
        int grid,
        bool isTileSelected);
};
