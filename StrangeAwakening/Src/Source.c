#include <stdlib.h>
#include <SDL3/SDL_main.h>

#include "Engine.h"

int main(int argc, char* argv[])
{
    Engine* engine = Engine_Create(1152, 768, 10, 2);
    if (!engine) return EXIT_FAILURE;

    while (engine->running)
    {
        Engine_Update(engine);
        Engine_Render(engine);
    }

    Engine_Free(engine);

    return EXIT_SUCCESS;
}
