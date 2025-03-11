#include "InterfaceEvents.h"

InterfaceEvents::InterfaceEvents(int eventsNumber)
    : eventsNumber(eventsNumber)
{
    keyboard = (Uint8*)SDL_GetKeyboardState(nullptr);

    events = new bool[eventsNumber]();
}

InterfaceEvents::~InterfaceEvents()
{
    delete events;
}

bool InterfaceEvents::Poll()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            events[0] = true;
            break;

        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key)
            {
            case SDLK_H:
                events[1] = true;
                break;
            case SDLK_C:
                events[2] = true;
            }
            break;

        case SDL_EVENT_QUIT:
            return false;
        }
    }

    float tX, tY;
    SDL_GetMouseState(&tX, &tY);

    mouseX = static_cast<int>(tX);
    mouseY = static_cast<int>(tY);

    return true;
}

void InterfaceEvents::Clear()
{
    for (int i = 0; i < eventsNumber; i++)
    {
        events[i] = false;
    }
}

Uint8* InterfaceEvents::GetKeyboard() const
{
    return keyboard;
}

int InterfaceEvents::GetMouseX() const
{
    return mouseX;
}

int InterfaceEvents::GetMouseY() const
{
    return mouseY;
}

bool* InterfaceEvents::GetEvents() const
{
    return events;
}
