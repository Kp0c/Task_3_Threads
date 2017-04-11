#pragma once
#include "parser.h"
#include "scaner.h"
#include "stringMutexQueue.h"

#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <sstream>

namespace ProjectParser
{

class ProjectAnalyzer
{
public:
	static std::stringstream Analyze(std::string path);

private:
	static std::stringstream FormOutput(const Statistic& stat, double time);
	static void ParseThread(Statistic& stat, StringMutexQueue& queue, const bool& is_done_searching);
};

} // namespace ProjectParser

