#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <thread>

#include "file.h"
#include "mutexFileQueue.h"
#include "scaner.h"

using namespace std;

static const std::string PATH = R"(D:\QT projects\Task_3_Threads)";

MutexFileQueue* myQueue;

void callback()
{
	cout << "end" << endl;
	while(!myQueue->isEmpty())
	{
		cout << myQueue->pop().path << endl;
	}
}
/*
void Parse(std::string path)
{
	std::ifstream file;
	file.open(path, ios::in);
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
				std::string comment_line = line.substr(line.find_first_not_of(' '));
				comment_line = comment_line.substr(comment_line.find_first_not_of('\t'),2);
				if(comment_line == "//")
				{
					comment_lines++;
				}
				else
					code_lines++;
			}
		}
		file.close();
	}
}
*/

int main()
{
	myQueue = new MutexFileQueue();
	Scaner scaner(myQueue);
	scaner.Scan(PATH, callback);
	//thread t1(Scan,PATH);
	//thread t2(Parse);
	//t1.join();
	//t2.join();
	/*Parse(PATH + R"(\main.cpp)");

	cout << blank_lines << endl;
	cout << comment_lines << endl;
	cout << code_lines << endl;*/

	return 0;
}
