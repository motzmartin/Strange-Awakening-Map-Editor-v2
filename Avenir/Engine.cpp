#include "Engine.h"

Engine::Engine(int windowWidth, int windowHeight, int eventsNumber, int texturesNumber)
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
        interfaceEvents->GetMouse(),
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
