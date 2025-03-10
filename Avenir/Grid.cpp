#include "Grid.h"

Grid::Grid()
{
    grid = new char* [15];

    for (int i = 0; i < 15; i++)
    {
        grid[i] = new char[20]();
    }
}

Grid::~Grid()
{
    for (int i = 0; i < 15; i++)
    {
        delete[] grid[i];
    }

    delete[] grid;
}

void Grid::Update(int selectedX, int selectedY, bool mouseDown, bool clear)
{
    if (clear)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                grid[i][j] = 0;
            }
        }
    }

    if (mouseDown)
    {
        grid[selectedY][selectedX] = (grid[selectedY][selectedX] + 1) % 2;
    }
}

void Grid::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (grid[i][j])
            {
                SDL_FRect rect =
                {
                    static_cast<float>(j) * 32.f,
                    static_cast<float>(i) * 32.f,
                    32.f,
                    32.f
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
