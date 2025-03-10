#pragma once

#include <SDL3/SDL.h>

class InterfaceEvents
{
private:
	Uint8* keyboard = nullptr;

	int mouseX = 0;
	int mouseY = 0;

	bool* events = nullptr;
	int eventsNumber = 0;

public:
	InterfaceEvents(int eventsNumber);
	~InterfaceEvents();

	bool Poll();
	void Clear();

	Uint8* GetKeyboard() const;
	int GetMouseX() const;
	int GetMouseY() const;
	bool* GetEvents() const;
};
