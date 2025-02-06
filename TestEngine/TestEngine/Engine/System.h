#pragma once

// includes
#include "MessageSystem.h"

class Engine;

class System
{
public:
	virtual ~System() {}

	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;

	void SendMessage(std::shared_ptr<Message> message, Engine& engine);
};