#include "Grid.h"

Grid::Grid()
{
    arr = new char* [15];

    for (int i = 0; i < 15; i++)
    {
        arr[i] = new char[20]();
    }
}

Grid::~Grid()
{
    for (int i = 0; i < 15; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;
}

void Grid::Update(int selectedX, int selectedY, bool mouseDown, bool clear)
{
    if (clear)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                arr[i][j] = 0;
            }
        }
    }

    if (mouseDown)
    {
        arr[selectedY][selectedX] = (arr[selectedY][selectedX] + 1) % 2;
    }
}

void Grid::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j])
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
