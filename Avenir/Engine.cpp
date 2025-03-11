#include "Engine.h"

Engine::Engine(int windowWidth, int windowHeight, int texturesNumber, int eventsNumber)
{
    display = std::make_unique<Display>(windowWidth, windowHeight, texturesNumber);
    if (!display->IsInitialized()) return;

    interfaceEvents = std::make_unique<InterfaceEvents>(eventsNumber);
    game = std::make_unique<Game>();

    initialized = true;
}

void Engine::Update()
{
    interfaceEvents->Clear();

    if (!interfaceEvents->Poll())
    {
        running = false;
        return;
    }

    game->Update(interfaceEvents->GetEvents(),
        interfaceEvents->GetMouseX(),
        interfaceEvents->GetMouseY(),
        interfaceEvents->GetKeyboard());
}

void Engine::Render()
{
    display->Clear(0, 0, 0);

    game->Draw(display->GetRenderer(), display->GetTextureLoader()->GetTextures());

    display->Render();
}

bool Engine::IsRunning() const
{
    return running;
}

bool Engine::IsInitialized() const
{
    return initialized;
}
