#include "Hud.h"

void Hud::Draw(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    int menu,
    int pointedX,
    int pointedY,
    int selectedX,
    int selectedY,
    std::vector<SDL_Point>* frontTiles,
    bool isTileSelected)
{
    if (menu == 1)
    {
        DrawInventory(renderer, sprites, pointedX, pointedY, selectedX, selectedY);
    }
    else if (menu == 2)
    {
        if (isTileSelected)
        {
            SDL_Rect hoveredRect = { pointedX * 4, pointedY * 4, 16, 16 };
            SDL_FRect hoveredRectF;
            SDL_RectToFRect(&hoveredRect, &hoveredRectF);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderRect(renderer, &hoveredRectF);
        }

        DrawFrontTiles(renderer, frontTiles, pointedX, pointedY);
    }
    else
    {
        SDL_Rect tileSrc = { selectedX * 16, selectedY * 16, 16, 16 };
        SDL_FRect tileSrcF;
        SDL_RectToFRect(&tileSrc, &tileSrcF);

        SDL_Rect tileDst = { pointedX * 4, pointedY * 4, 16, 16 };
        SDL_FRect tileDstF;
        SDL_RectToFRect(&tileDst, &tileDstF);

        SDL_RenderTexture(renderer, sprites, &tileSrcF, &tileDstF);
    }
}

void Hud::DrawInventory(SDL_Renderer* renderer,
    SDL_Texture* sprites,
    int pointedX,
    int pointedY,
    int selectedX,
    int selectedY)
{
    SDL_Rect backgroundRect = { 0, 0, 640, 384 };
    SDL_FRect backgroundRectF;
    SDL_RectToFRect(&backgroundRect, &backgroundRectF);

    SDL_SetRenderDrawColor(renderer, 63, 63, 63, 255);
    SDL_RenderFillRect(renderer, &backgroundRectF);

    SDL_Rect inventoryRect = { 256, 128, 128, 128 };
    SDL_FRect inventoryRectF;
    SDL_RectToFRect(&inventoryRect, &inventoryRectF);

    SDL_RenderTexture(renderer, sprites, nullptr, &inventoryRectF);

    SDL_Rect pointedRect = { pointedX * 16, pointedY * 16, 16, 16 };
    SDL_FRect pointedRectF;
    SDL_RectToFRect(&pointedRect, &pointedRectF);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &pointedRectF);

    if (pointedX - 16 != selectedX || pointedY - 8 != selectedY)
    {
        SDL_Rect selectedRect = { 256 + selectedX * 16, 128 + selectedY * 16, 16, 16 };
        SDL_FRect selectedRectF;
        SDL_RectToFRect(&selectedRect, &selectedRectF);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderRect(renderer, &selectedRectF);
    }
}

void Hud::DrawFrontTiles(SDL_Renderer* renderer,
    std::vector<SDL_Point>* frontTiles,
    int pointedX,
    int pointedY)
{
    for (int i = 0; i < frontTiles->size(); i++)
    {
        if (pointedX != (*frontTiles)[i].x || pointedY != (*frontTiles)[i].y)
        {
            SDL_Rect frontRect = { (*frontTiles)[i].x * 4, (*frontTiles)[i].y * 4, 16, 16 };
            SDL_FRect frontRectF;
            SDL_RectToFRect(&frontRect, &frontRectF);

            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderRect(renderer, &frontRectF);
        }
    }
}
