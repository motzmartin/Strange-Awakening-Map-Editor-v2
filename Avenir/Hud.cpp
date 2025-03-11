#include "Hud.h"

void Hud::Update(int mouseX, int mouseY, bool showInventory)
{
    if (inventory != showInventory)
    {
        if (!showInventory)
        {
            tileSelectedX = hoveredX - 16;
            tileSelectedY = hoveredY - 8;
        }

        inventory = showInventory;
    }

    if (inventory)
    {
        hoveredX = mouseX / 32;
        hoveredY = mouseY / 32;

        if (hoveredX < 16) hoveredX = 16;
        else if (hoveredX > 23) hoveredX = 23;

        if (hoveredY < 8) hoveredY = 8;
        else if (hoveredY > 15) hoveredY = 15;
    }
    else
    {
        hoveredX = (mouseX - 12) / 8;
        hoveredY = (mouseY - 12) / 8;
    }
}

void Hud::Draw(SDL_Renderer* renderer, SDL_Texture* sprites)
{
    if (inventory)
    {
        SDL_FRect rect = { 0.f, 0.f, 640.f, 384.f };

        SDL_SetRenderDrawColor(renderer, 63, 63, 63, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_FRect spritesDst = { 256.f, 128.f, 128.f, 128.f };

        SDL_RenderTexture(renderer, sprites, nullptr, &spritesDst);

        SDL_FRect hoveredDst =
        {
            static_cast<float>(hoveredX) * 16.f,
            static_cast<float>(hoveredY) * 16.f,
            16.f,
            16.f
        };

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &hoveredDst);

        if (hoveredX - 16 != tileSelectedX || hoveredY - 8 != tileSelectedY)
        {
            SDL_FRect selectedRect =
            {
                256.f + static_cast<float>(tileSelectedX) * 16.f,
                128.f + static_cast<float>(tileSelectedY) * 16.f,
                16.f,
                16.f
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderRect(renderer, &selectedRect);
        }
    }
    else
    {
        SDL_FRect tileSrc =
        {
            static_cast<float>(tileSelectedX) * 16.f,
            static_cast<float>(tileSelectedY) * 16.f,
            16.f,
            16.f
        };

        SDL_FRect tileDst =
        {
            static_cast<float>(hoveredX) * 4.f,
            static_cast<float>(hoveredY) * 4.f,
            16.f,
            16.f
        };

        SDL_RenderTexture(renderer, sprites, &tileSrc, &tileDst);
    }
}

int Hud::GetHoveredX() const
{
    return hoveredX;
}

int Hud::GetHoveredY() const
{
    return hoveredY;
}

int Hud::GetTileSelectedX() const
{
    return tileSelectedX;
}

int Hud::GetTileSelectedY() const
{
    return tileSelectedY;
}
