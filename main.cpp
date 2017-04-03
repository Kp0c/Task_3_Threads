#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

#include "scaner.h"
#include "parser.h"
#include "stringMutexQueue.h"

static const std::string PATH = R"(D:\boost_1_63_0\boost)";

std::atomic<int> proceced_files;
std::atomic<int> total_lines;
std::atomic<int> blank_lines;
std::atomic<int> comment_lines;
std::atomic<int> code_lines;

bool is_done = false;
StringMutexQueue queue;

void ParseThread()
{
	parser::Parser parser;
	parser::Statistic stat;
	std::string parse_path;

	while(!is_done || !queue.isEmpty())
	{
		if(!queue.isEmpty())
		{
			parse_path = queue.pop();
			stat = parser.Parse2(parse_path);

			std::cout << "parsing " << parse_path << std::endl;

			total_lines += stat.line_count;
			blank_lines += stat.blank_lines;
			comment_lines += stat.comment_lines;
			code_lines += stat.code_lines;
			proceced_files += 1;
		}
	}
}

void callback(std::string path)
{
	queue.add(path);
	std::cout << "found new file" << std::endl;
}

int main()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	scaner::Scaner scnr;

	int hardware_concurrency = std::thread::hardware_concurrency() + 1;
	std::thread* threads = new std::thread[hardware_concurrency];

	for(int i = 0; i < hardware_concurrency; i++)
	{
		threads[i] = std::thread(ParseThread);
	}

	scnr.Scan(PATH, std::regex(R"(^.*[.](c|cpp|h|hpp)$)"), callback, [] { is_done = true; });

	ParseThread();

	for(int i = 0; i < hardware_concurrency; i++)
	{
		threads[i].join();
	}

	end = std::chrono::system_clock::now();

	std::cout << "Blank: " << blank_lines << std::endl;
	std::cout << "Comment: " << comment_lines << std::endl;
	std::cout << "Code: " << code_lines << std::endl;
	std::cout << "Total: " << total_lines << std::endl;
	std::cout << "Files: " << proceced_files << std::endl;

	std::chrono::duration<double> elapsed_seconds = end-start;

	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

	delete[] threads;

	return 0;
}
