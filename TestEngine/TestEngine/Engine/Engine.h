#pragma once
// includes
#include <vector>
#include <memory>
#include <functional>
#include <chrono>
#include "MessageSystem.h"
#include "WindowSystem.h"

class System;

class Engine
{
public:
	Engine();
	~Engine();

	void Initialize();
	void Update();
	void Shutdown();

	// Messaging system for system communication
	inline MessageSystem& GetMessageSystem() { return m_messageSystem; };

	inline float GetDeltaTime() const { return dt; };

	// System registration
	void RegisterSystem(std::shared_ptr<System> system);

private:
	std::vector<std::shared_ptr<System>> m_pSystems;
	MessageSystem m_messageSystem;
	std::shared_ptr<WindowSystem> m_windowSystem;

	std::chrono::high_resolution_clock::time_point lastFrameTime;
	float dt;
};

