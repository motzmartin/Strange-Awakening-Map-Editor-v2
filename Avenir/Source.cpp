#include <SDL3/SDL_main.h>

#include "Engine.h"

int SDL_main(int argc, char* argv[])
{
    Engine engine(640, 480, 3, 3);

    if (!engine.IsInitialized())
    {
        return 1;
    }

    while (engine.IsRunning())
    {
        engine.Update();
        engine.Render();
    }

    return 0;
}
