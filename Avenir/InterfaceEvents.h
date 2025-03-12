#pragma once

#include <SDL3/SDL.h>

class InterfaceEvents
{
private:
	Uint8* keyboard = nullptr;

	SDL_FPoint mouse = { 0 };

	bool* events = nullptr;
	int eventsNumber = 0;

public:
	InterfaceEvents(int eventsNumber);
	~InterfaceEvents();

	bool Poll();
	void Clear();

	Uint8* GetKeyboard() const;
	SDL_FPoint GetMouse() const;
	bool* GetEvents() const;
};
