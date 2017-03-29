#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <thread>

#include "file.h"
#include "mutexFileQueue.h"
#include "scaner.h"
#include "parser.h"

using namespace std;

static const std::string PATH = R"(D:\QT projects\Task_3_Threads)";

MutexFileQueue* myQueue;
Parser* parser = new Parser();

void callback(File file)
{
	cout << file.path << endl;
	parser->Parse(file.path);
}

int main()
{
	myQueue = new MutexFileQueue();
	Scaner scaner(myQueue);
	scaner.Scan(PATH, callback);

	return 0;
}
