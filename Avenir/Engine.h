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
	Engine(int windowWidth, int windowHeight, int texturesNumber, int eventsNumber);

	void Update();
	void Render();

	bool IsRunning() const;
	bool IsInitialized() const;
};
