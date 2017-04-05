#pragma once
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <sstream>

#include "parser.h"
#include "scaner.h"
#include "stringMutexQueue.h"

namespace project_analyzer
{

class ProjectAnalyzer
{
public:
	static std::shared_ptr<std::stringstream> Analyze(std::string path);

private:
	static std::shared_ptr<std::stringstream> FormOutput(std::shared_ptr<const parser::Statistic> stat, double time);
	static void ParseThread(std::shared_ptr<parser::Statistic> stat, std::shared_ptr<StringMutexQueue> queue,
					 std::shared_ptr<const bool> is_done_searching);
};

}

