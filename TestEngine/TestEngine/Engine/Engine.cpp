// includes
#include "Engine.h"
#include "System.h"
#include "Graphics.h"

Engine::Engine() :
	dt(0.0f)
{
	// TODO: Initialize message system and any other components
	lastFrameTime = std::chrono::high_resolution_clock::now();
}

Engine::~Engine()
{
	Shutdown();
}

void Engine::RegisterSystems()
{
	/*
	* All systems should be created and registered here.
	* This helps consolidate the amount of files that systems are touching.
	*/

	// Window system
	m_windowSystem = std::make_shared<WindowSystem>(800, 600, "2D Engine");
	m_pSystems.push_back(m_windowSystem);

	// Graphics system
	std::shared_ptr<Graphics> graphicsSystem = std::make_shared<Graphics>();
	m_pSystems.push_back(graphicsSystem);

	// IMGUI system

	// Physics System

	// Animation System
}

void Engine::Initialize()
{
	// Create and register systems
	RegisterSystems();

	// Initialize all systems
	for (auto& system : m_pSystems)
	{
		system->Initialize();
	}

	// Store the WindowSystem (assuming the first system is the WindowSystem)
	m_windowSystem = std::dynamic_pointer_cast<WindowSystem>(m_pSystems[0]);
}

void Engine::Update()
{
	// Main engine loop
	bool bIsRunning = true;

	while (bIsRunning)
	{
		// Calculate delta time
		auto currentFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> frameDuration = currentFrameTime - lastFrameTime;
		dt = frameDuration.count(); // In seconds

		// Update last frame time
		lastFrameTime = currentFrameTime;

		// Process messages prior to updating systems
		m_messageSystem.ProcessMessages();

		// Render/Update systems
		for (auto& system : m_pSystems)
		{
			system->Update(dt);
			system->Render();
		}

		// Break this loop if the window should be closed
		// TODO: Change this to use the messaging system. All things should be handled via messaging system
		if (m_windowSystem && m_windowSystem->ShouldClose())
		{
			bIsRunning = false;
		}
	}
}

void Engine::Shutdown()
{
	for (auto& system : m_pSystems)
	{
		system->Shutdown();
	}
}

void Engine::RegisterSystem(std::shared_ptr<System> system)
{
	m_pSystems.push_back(system);
}
