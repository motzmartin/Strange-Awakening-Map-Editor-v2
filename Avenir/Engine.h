#pragma once

#include "Display.h"
#include "InterfaceEvents.h"
#include "Game.h"

class Engine
{
private:
	Display display;
	InterfaceEvents interfaceEvents;
	Game game;

	bool running = true;
	bool initialized = false;

public:
	Engine(unsigned int windowWidth, unsigned int windowHeight);

	void Update();
	void Render();

	bool IsRunning() const;
	bool IsInitialized() const;
};
