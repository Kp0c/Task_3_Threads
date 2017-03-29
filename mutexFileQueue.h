#pragma once
#include <queue>
#include <mutex>

#include "file.h"

class MutexFileQueue
{
public:
	MutexFileQueue() { }

	void add(File element)
	{
		m_mutex.lock();
		m_queue.push(element);
		m_mutex.unlock();
	}

	File pop()
	{
		m_mutex.lock();
		File temp = m_queue.front();
		m_queue.pop();
		m_mutex.unlock();

		return temp;
	}

	bool isEmpty(){
		return m_queue.empty();
	}

private:
	std::queue<File> m_queue;
	std::mutex m_mutex;
};
