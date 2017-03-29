#include "parser.h"

Parser::Parser(MutexQueue* files, int threads_count) : m_threads_count(threads_count), m_files(files)
{
	threads = new std::thread[threads_count];
}

void Parser::Start()
{

}

void Parser::Stop()
{

}
