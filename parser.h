#pragma once
#include <thread>
#include "mutexFileQueue.h"
#include "file.h"

class Parser
{
public:
	Parser(/*MutexQueue<File>* files, int threads_count = 5*/);

	void Parse(std::string path);
private:
	//int m_threads_count;
	//MutexQueue<File>* m_files;
	//std::thread threads[];
};
