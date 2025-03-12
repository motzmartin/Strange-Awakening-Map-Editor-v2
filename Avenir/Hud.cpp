#include "Hud.h"

void Hud::Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    SDL_FPoint pointed,
    SDL_FPoint selected,
    std::vector<SDL_FPoint>* frontTiles,
    int mode,
    int grid,
    bool isTileSelected)
{
    if (mode == 1)
    {
        SDL_SetTextureAlphaMod(sprites, 255);

        DrawInventory(renderer, sprites, pointed, selected);
    }
    else if (mode == 2 || mode == 3)
    {
        if (isTileSelected)
        {
            SDL_FRect hoveredRect = { pointed.x * 4.f, pointed.y * 4.f, 16.f, 16.f };
            if (mode == 2)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else if (mode == 3)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
            SDL_RenderRect(renderer, &hoveredRect);
        }

        DrawFrontTiles(renderer, frontTiles, pointed, isTileSelected);
    }
    else
    {
        SDL_SetTextureAlphaMod(sprites, 191);

        SDL_FRect tileSrc = { selected.x * 16.f, selected.y * 16.f, 16.f, 16.f };
        SDL_FRect tileDst = { pointed.x * 4.f, pointed.y * 4.f, 16.f, 16.f };
        SDL_RenderTexture(renderer, sprites, &tileSrc, &tileDst);

        if (grid != 0)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 15);

            for (int i = 0; i < 40; i++)
            {
                SDL_FRect rect = { static_cast<float>(i) * 16.f, 0.f, 1.f, 384.f };
                SDL_RenderRect(renderer, &rect);
            }

            for (int i = 0; i < 24; i++)
            {
                SDL_FRect rect = { 0.f, static_cast<float>(i) * 16.f, 640.f, 1.f };
                SDL_RenderRect(renderer, &rect);
            }

            if (grid == 2)
            {
                for (int i = 0; i < 160; i++)
                {
                    SDL_FRect rect = { static_cast<float>(i) * 4.f, 0.f, 1.f, 384.f };
                    SDL_RenderRect(renderer, &rect);
                }

                for (int i = 0; i < 96; i++)
                {
                    SDL_FRect rect = { 0.f, static_cast<float>(i) * 4.f, 640.f, 1.f };
                    SDL_RenderRect(renderer, &rect);
                }
            }
        }
    }
}

void Hud::DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    SDL_FPoint pointed,
    SDL_FPoint selected)
{
    SDL_FRect backgroundRect = { 0.f, 0.f, 640.f, 384.f };
    SDL_SetRenderDrawColor(renderer, 63, 63, 63, 255);
    SDL_RenderFillRect(renderer, &backgroundRect);

    SDL_FRect inventoryRect = { 256.f, 128.f, 128.f, 128.f };
    SDL_RenderTexture(renderer, sprites, nullptr, &inventoryRect);

    SDL_FRect pointedRect = { pointed.x * 16.f, pointed.y * 16.f, 16.f, 16.f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &pointedRect);

    if (pointed.x - 16.f != selected.x || pointed.y - 8.f != selected.y)
    {
        SDL_FRect selectedRect = { (selected.x + 16.f) * 16.f, (selected.y + 8.f) * 16, 16.f, 16.f };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderRect(renderer, &selectedRect);
    }
}

void Hud::DrawFrontTiles(SDL_Renderer* renderer,
    std::vector<SDL_FPoint>* frontTiles,
    SDL_FPoint pointed,
    bool isTileSelected)
{
    for (int i = 0; i < frontTiles->size(); i++)
    {
        if (!isTileSelected || (pointed.x != (*frontTiles)[i].x || pointed.y != (*frontTiles)[i].y))
        {
            SDL_FRect frontRect = { (*frontTiles)[i].x * 4.f, (*frontTiles)[i].y * 4.f, 16.f, 16.f };
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderRect(renderer, &frontRect);
        }
    }
}
