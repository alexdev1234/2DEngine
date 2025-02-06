// includes
#include <iostream>

// system includes
#include "Engine.h"
#include "WindowSystem.h"


int main()
{
	Engine* engine = new Engine();

	// Initialize and run the engine
	engine->Initialize();
	engine->Update();
	engine->Shutdown();

	// Free engine memory
	delete engine;
}