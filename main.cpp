#include "projectAnalyzer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void PrintFile(const std::string& text, const std::string& path)
{
	std::ofstream file;
	file.open(path, std::ios::out);
	if (file.is_open())
	{
		file << text;
		file.close();
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Wrong argument" << std::endl;
		return -1;
	}

	std::string stream(ProjectParser::ProjectAnalyzer::Analyze(argv[1]).str());

	//print statistic
	std::cout << stream;
	PrintFile(stream, "results.txt");

	return 0;
}
