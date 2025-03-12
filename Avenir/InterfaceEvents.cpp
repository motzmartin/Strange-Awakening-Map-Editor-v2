#include "InterfaceEvents.h"

InterfaceEvents::InterfaceEvents(int _eventsNumber)
{
    keyboard = (Uint8*)SDL_GetKeyboardState(nullptr);

    eventsNumber = _eventsNumber;
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
            switch (event.key.scancode)
            {
            case SDL_SCANCODE_G:
                events[1] = true;
            }
            break;

        case SDL_EVENT_QUIT:
            return false;
        }
    }

    SDL_GetMouseState(&mouse.x, &mouse.y);

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

SDL_FPoint InterfaceEvents::GetMouse() const
{
    return mouse;
}

bool* InterfaceEvents::GetEvents() const
{
    return events;
}
