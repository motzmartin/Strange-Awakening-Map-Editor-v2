#include "Hud.h"

void Hud::Update(int mouseX, int mouseY, bool trigger)
{
    if (trigger) enabled = !enabled;

    selectedX = mouseX / 32;

    if (selectedX < 0) selectedX = 0;
    else if (selectedX > 31)  selectedX = 31;

    selectedY = mouseY / 32;

    if (selectedY < 0) selectedY = 0;
    else if (selectedY > 31) selectedY = 31;
}

void Hud::Draw(SDL_Renderer* renderer,
    int mouseX,
    int mouseY,
    SDL_Texture* cursor,
    SDL_Texture* grid,
    SDL_Texture* selection)
{
    SDL_RenderTexture(renderer, grid, nullptr, nullptr);

    SDL_FRect selectionDst =
    {
        static_cast<float>(selectedX) * 32.f,
        static_cast<float>(selectedY) * 32.f,
        32.f,
        32.f
    };
    SDL_RenderTexture(renderer, selection, nullptr, &selectionDst);

    SDL_FRect cursorDst =
    {
        static_cast<float>(mouseX),
        static_cast<float>(mouseY),
        14.f,
        14.f
    };
    SDL_RenderTexture(renderer, cursor, nullptr, &cursorDst);
}

int Hud::GetSelectedX() const { return selectedX; }

int Hud::GetSelectedY() const { return selectedY; }

bool Hud::IsEnabled() const { return enabled; }
