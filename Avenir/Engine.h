#pragma once

#include <memory>

#include "Display.h"
#include "InterfaceEvents.h"
#include "Game.h"

class Engine
{
private:
	std::unique_ptr<Display> display;
	std::unique_ptr<InterfaceEvents> interfaceEvents;
	std::unique_ptr<Game> game;

	bool running = true;
	bool initialized = false;

public:
	Engine(int windowWidth, int windowHeight, int texturesNumber, int eventsNumber);

	void Update();
	void Render();

	bool IsRunning() const;
	bool IsInitialized() const;
};
