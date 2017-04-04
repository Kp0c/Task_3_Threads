#pragma once
#include <string>
#include <regex>
#include <fstream>
#include <atomic>

namespace parser {

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
	static void Parse(std::string path, Statistic* stat);
private:
	//static const std::regex blank_line_regex = R"(^\s*$)";
	//static const std::regex comment_line_regex = R"(\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+)";
};

}
