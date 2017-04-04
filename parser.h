#pragma once
#include <string>
#include <regex>
#include <fstream>
#include <atomic>
#include <memory>

namespace parser
{

struct Statistic
{
	std::atomic<int> blank_lines;
	std::atomic<int> comment_lines;
	std::atomic<int> code_lines;
	std::atomic<int> line_count;
	std::atomic<int> processed_files;
};

class Parser
{
public:
	static void Parse(std::string path, std::shared_ptr<Statistic> stat);
};

}
