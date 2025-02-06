// includes
#include <iostream>

// system includes
#include "Engine.h"
#include "WindowSystem.h"


int main()
{
	Engine engine;

	// Create and register systems
	auto windowSystem = std::make_shared<WindowSystem>(800, 600, "2D Engine");
	engine.RegisterSystem(windowSystem);

	// Initialize and run the engine
	engine.Initialize();
	engine.Update();
	engine.Shutdown();
}