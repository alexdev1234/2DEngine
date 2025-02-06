// includes
#include "Engine.h"
#include "System.h"

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

void Engine::Initialize()
{
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

		// Update systems
		for (auto& system : m_pSystems)
		{
			system->Update(dt);
		}

		// Break this loop if the window should be closed
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
