// includes
#include <iostream>
#include "Graphics/WindowSystem.h"

int main()
{
	// Create the window
	std::cout << "Creating window" << std::endl;
	WindowSystem window(800, 600, "2D Engine");

	while (!window.ShouldClose())
	{
		window.SetClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		window.Update();
	}

	std::cout << "Exiting application..." << std::endl;
	return 0;
}