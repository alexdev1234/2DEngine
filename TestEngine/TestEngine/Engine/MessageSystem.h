#pragma once

// includes
#include <queue>
#include <memory>
#include <functional>

class Message
{
public:
	virtual ~Message() {}
	virtual void Process() = 0;
};

// special system that allows various systems to communicate with one another
class MessageSystem
{
public:
	void SendMessage(std::shared_ptr<Message> message);
	void ProcessMessages();

private:
	std::queue<std::shared_ptr<Message>> m_messageQueue;

};