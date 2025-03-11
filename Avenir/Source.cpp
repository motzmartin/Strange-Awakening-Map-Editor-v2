#include <SDL3/SDL_main.h>

#include "Engine.h"

int SDL_main(int argc, char* argv[])
{
    Engine engine(1280, 768, 1, 1);

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
