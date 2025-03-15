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

        case SDL_EVENT_KEY_DOWN:
            switch (event.key.scancode)
            {
            case SDL_SCANCODE_G:
                interfaceEvents->events[1] = true;
                break;
            case SDL_SCANCODE_LEFT:
                interfaceEvents->events[2] = true;
                break;
            case SDL_SCANCODE_UP:
                interfaceEvents->events[3] = true;
                break;
            case SDL_SCANCODE_RIGHT:
                interfaceEvents->events[4] = true;
                break;
            case SDL_SCANCODE_DOWN:
                interfaceEvents->events[5] = true;
                break;
            case SDL_SCANCODE_X:
                interfaceEvents->events[6] = true;
                break;
            case SDL_SCANCODE_L:
                interfaceEvents->events[7] = true;
            }
            break;

        case SDL_EVENT_QUIT:
            return false;
        }
    }

    float mouseX = 0;
    float mouseY = 0;

    SDL_GetMouseState(&mouseX, &mouseY);

    interfaceEvents->mouse = Vector_New((int)mouseX, (int)mouseY);

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
