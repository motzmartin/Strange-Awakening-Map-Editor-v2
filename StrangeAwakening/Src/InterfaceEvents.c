#include "InterfaceEvents.h"

InterfaceEvents* InterfaceEvents_Create(int eventsNumber)
{
    InterfaceEvents* interfaceEvents = calloc(1, sizeof(InterfaceEvents));
    if (!interfaceEvents) return NULL;

    interfaceEvents->keyboard = (Uint8*)SDL_GetKeyboardState(NULL);

    interfaceEvents->events = calloc(eventsNumber, sizeof(bool));
    if (!interfaceEvents->events) return NULL;

    interfaceEvents->eventsNumber = eventsNumber;

    return interfaceEvents;
}

bool InterfaceEvents_Poll(InterfaceEvents* interfaceEvents)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                interfaceEvents->events[0] = true;
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                interfaceEvents->events[1] = true;
            }
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            if (event.wheel.y > 0.f)
            {
                interfaceEvents->events[2] = true;
            }
            else if (event.wheel.y < 0.f)
            {
                interfaceEvents->events[3] = true;
            }
            break;

        case SDL_EVENT_QUIT:
            return false;
        }
    }

    VectorF mousePos = { 0 };
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    interfaceEvents->mouse = VectorConversion_FromVectorF(mousePos);

    return true;
}

void InterfaceEvents_Clear(InterfaceEvents* interfaceEvents)
{
    for (int i = 0; i < interfaceEvents->eventsNumber; i++)
    {
        interfaceEvents->events[i] = false;
    }
}

void InterfaceEvents_Free(InterfaceEvents* interfaceEvents)
{
    free(interfaceEvents->events);

    free(interfaceEvents);
}
