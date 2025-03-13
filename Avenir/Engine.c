#include "Engine.h"

Engine* Engine_Create(int windowWidth,
    int windowHeight,
    int eventsNumber,
    int texturesNumber)
{
    Engine* engine = calloc(1, sizeof(Engine));
    if (!engine) return NULL;

    engine->display = Display_Create(windowWidth, windowHeight, texturesNumber);
    if (!engine->display) return NULL;

    engine->interfaceEvents = InterfaceEvents_Create(eventsNumber);
    if (!engine->interfaceEvents) return NULL;

    engine->game = Game_Create();
    if (!engine->game) return NULL;

    engine->running = true;

    return engine;
}

void Engine_Update(Engine* engine)
{
    InterfaceEvents_Clear(engine->interfaceEvents);

    if (!InterfaceEvents_Poll(engine->interfaceEvents))
    {
        engine->running = false;
        return;
    }

    Game_Update(engine->game,
        engine->interfaceEvents->events,
        engine->interfaceEvents->mouse,
        engine->interfaceEvents->keyboard);
}

void Engine_Render(Engine* engine)
{
    Display_Clear(engine->display, 0, 0, 0);

    Game_Draw(engine->game,
        engine->display->renderer,
        engine->display->textureLoader->textures);

    Display_Render(engine->display);
}

void Engine_Free(Engine* engine)
{
    Game_Free(engine->game);
    InterfaceEvents_Free(engine->interfaceEvents);
    Display_Free(engine->display);

    free(engine);
}
