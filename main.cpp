#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "projectAnalyzer.h"

void PrintConsole(std::shared_ptr<const std::stringstream> string)
{
	std::cout << string->str();
}

void PrintFile(std::shared_ptr<const std::stringstream> string, std::string path)
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

	std::shared_ptr<std::stringstream> stream = project_analyzer::ProjectAnalyzer::Analyze(argv[1]);

	//print statistic
	PrintConsole(stream);
	PrintFile(stream, "results.txt");

	return 0;
}
