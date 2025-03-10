#include "Engine.h"

Engine::Engine(unsigned int windowWidth, unsigned int windowHeight)
    : display(windowWidth, windowHeight, 3),
    interfaceEvents(3)
{
    if (!display.IsInitialized()) return;

    initialized = true;
}

void Engine::Update()
{
    interfaceEvents.Clear();

    if (!interfaceEvents.Poll())
    {
        running = false;
        return;
    }

    game.Update(interfaceEvents.GetEvents(),
        interfaceEvents.GetKeyboard(),
        interfaceEvents.GetMouseX(),
        interfaceEvents.GetMouseY());
}

void Engine::Render()
{
    display.Clear();

    game.GetGrid()->Draw(display.GetRenderer());

    if (game.GetHud()->IsEnabled())
    {
        game.GetHud()->Draw(display.GetRenderer(),
            interfaceEvents.GetMouseX(),
            interfaceEvents.GetMouseY(),
            display.GetTextureLoader()->GetTexture(0),
            display.GetTextureLoader()->GetTexture(1),
            display.GetTextureLoader()->GetTexture(2));
    }

    display.Render();
}

bool Engine::IsRunning() const { return running; }

bool Engine::IsInitialized() const { return initialized; }
