#pragma once
#include <queue>
#include <mutex>

class StringMutexQueue
{
public:
	StringMutexQueue() = default;

	void add(std::string element)
	{
		m_mutex.lock();
		m_queue.push(element);
		m_mutex.unlock();
	}

	std::string pop()
	{
		m_mutex.lock();
		std::string temp = m_queue.front();
		m_queue.pop();
		m_mutex.unlock();

		return temp;
	}

	bool isEmpty(){
		return m_queue.empty();
	}

private:
	std::queue<std::string> m_queue;
	std::mutex m_mutex;
};
