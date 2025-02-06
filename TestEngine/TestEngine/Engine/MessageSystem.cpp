// includes
#include "MessageSystem.h"
#include <iostream>

void MessageSystem::SendMessage(std::shared_ptr<Message> message)
{
	m_messageQueue.push(message);
}

void MessageSystem::ProcessMessages()
{
	while (!m_messageQueue.empty())
	{
		auto message = m_messageQueue.front();
		m_messageQueue.pop();
		message->Process();
	}
}