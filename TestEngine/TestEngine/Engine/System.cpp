// includes
#include "System.h"
#include "Engine.h"

void System::SendMessage(std::shared_ptr<Message> message, Engine& engine)
{
	engine.GetMessageSystem().SendMessage(message);
}