#pragma once

#include <string>
#include <regex>
#include <fstream>
#include <atomic>
#include <memory>
#include <cctype>

namespace ProjectParser
{

struct Statistic
{
	std::atomic<unsigned> blank_lines;
	std::atomic<unsigned> comment_lines;
	std::atomic<unsigned> code_lines;
	std::atomic<unsigned> line_count;
	std::atomic<unsigned> processed_files;

	Statistic()
	{
		blank_lines = 0;
		comment_lines = 0;
		code_lines = 0;
		line_count = 0;
		processed_files = 0;
	}
};

class Parser
{
public:
	static void Parse(const std::string& path, Statistic& stat);
};

} // namespace ProjectAnalyzer
