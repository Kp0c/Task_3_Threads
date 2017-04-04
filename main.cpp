#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <sstream>

#include "scaner.h"
#include "parser.h"
#include "stringMutexQueue.h"

void ParseThread(parser::Statistic* stat, StringMutexQueue* queue, const bool* is_done_searching)
{
	std::string parse_path;

	while(!*is_done_searching || !queue->isEmpty())
	{
		parse_path = queue->pop();
		if(!parse_path.empty())
		{
			parser::Parser::Parse(parse_path, stat);
		}
	}
}

std::stringstream FormOutput(const parser::Statistic* stat, double time)
{
	std::stringstream stream;

	stream << "Blank: " << stat->blank_lines << std::endl;
	stream << "Comment: " << stat->comment_lines << std::endl;
	stream << "Code: " << stat->code_lines << std::endl;
	stream << "Total: " << stat->line_count << std::endl;
	stream << "Files: " << stat->processed_files << std::endl;
	stream << "Elapsed time: " << time << "s" << std::endl;

	return stream;
}

void PrintConsole(const std::stringstream* string)
{
	std::cout << string->str();
}

void PrintFile(const std::stringstream* string, std::string path)
{
	std::ofstream file;
	file.open(path, std::ios::out);
	if(file.is_open())
	{
		file << string->str();
		file.close();
	}
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "Wrong argument" << std::endl;
		return -1;
	}

	//note the time
	auto start = std::chrono::system_clock::now();

	//take hardware core count for parallel parsing.
	int hardware_concurrency = std::thread::hardware_concurrency();
	std::thread* threads = new std::thread[hardware_concurrency];

	//initializating
	std::shared_ptr<parser::Statistic> stat(new parser::Statistic {0, 0, 0, 0, 0});
	std::shared_ptr<StringMutexQueue> queue(new StringMutexQueue());
	bool is_done_searching = false;

	//start threads for parse
	for(int i = 0; i < hardware_concurrency; i++)
	{
		threads[i] = std::thread(ParseThread, stat.get(), queue.get(), &is_done_searching);
	}

	//start thread for scan
	scaner::Scaner::Scan(argv[1], std::regex(R"(^.*[.](c|cpp|h|hpp)$)"),
			[&queue] (std::string path) { queue->add(path); },
			[&is_done_searching] { is_done_searching = true; });

	//after scan help parse by main thread
	ParseThread(stat.get(), queue.get(), &is_done_searching);

	//wait untill each thread end parsing
	for(int i = 0; i < hardware_concurrency; i++)
	{
		threads[i].join();
	}

	delete[] threads;

	//note the time
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;

	//print statistic
	std::stringstream stream(FormOutput(stat.get(), elapsed_seconds.count()));
	PrintConsole(&stream);
	PrintFile(&stream, "test.txt");

	return 0;
}
