#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <thread>

#include "file.h"
#include "mutexFileQueue.h"
#include "scaner.h"

using namespace std;

static const std::string PATH = R"(D:\boost_1_63_0\boost\accumulators\framework)";

MutexFileQueue* myQueue;

void ParseFile(std::string path)
{
	std::ifstream file;
	file.open(path, ios::in);
	int blank_lines = 0;
	int comment_lines = 0;
	int code_lines = 0;

	if (file.is_open())
	{
		std::string line;
		while ( getline (file,line) )
		{
			if(line == "")
			{
				blank_lines++;
			}
			else
			{
				line = line.substr(line.find_first_not_of('\t'));
				std::string comment_line = line.substr(line.find_first_not_of(' '));
				//comment_line = comment_line.substr(comment_line.find_first_not_of('\t'),2);
				if(line.substr(0,2) == "//")
				{
					comment_lines++;
				}
				else
					code_lines++;
			}
		}
		file.close();
	}

	std::cout << "File: " << path << std::endl;
	std::cout << "Blank lines: " << blank_lines << std::endl;
	std::cout << "Comment lines: " << comment_lines << std::endl;
	std::cout << "Code lines: " << code_lines << std::endl;
}

void callback(File file)
{
	thread new_thread(ParseFile, file.path);
	new_thread.join();
	//parser->Parse(file.path);
}

int main()
{
	myQueue = new MutexFileQueue();
	Scaner scaner(myQueue);
	scaner.Scan(PATH, callback);

	return 0;
}
