#pragma once
#include <queue>
#include <mutex>

namespace ProjectParser
{

class StringMutexQueue
{
public:
	void Add(std::string element)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push(element);
	}

	std::string Pop()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		std::string temp;
		if (!queue_.empty())
		{
			temp = queue_.front();
			queue_.pop();
		}
		return temp;
	}

	bool IsEmpty() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.empty();
	}

private:
	std::queue<std::string> queue_;
	mutable std::mutex mutex_;
};

} // namespace ProjectParser
