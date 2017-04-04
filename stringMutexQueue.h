#pragma once
#include <queue>
#include <mutex>

class StringMutexQueue
{
public:
	StringMutexQueue() = default;

	void Add(std::string element)
	{
		std::lock_guard<std::mutex> lk(m_mutex);

		m_queue.push(element);
	}

	std::string Pop()
	{
		std::lock_guard<std::mutex> lk(m_mutex);

		std::string temp("");
		if(!m_queue.empty())
		{
			temp = m_queue.front();
			m_queue.pop();
		}

		return temp;
	}

	bool IsEmpty() const
	{
		std::lock_guard<std::mutex> lk(m_mutex);

		return m_queue.empty();
	}

private:
	std::queue<std::string> m_queue;
	mutable std::mutex m_mutex;
};
