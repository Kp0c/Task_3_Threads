#pragma once
#include <string>
#include <regex>
#include <fstream>

namespace parser {

struct Statistic
{
	int blank_lines;
	int comment_lines;
	int code_lines;
	int line_count;
};

class Parser
{
public:
	Statistic Parse(std::string path);
	Statistic Parse2(std::string path);
private:
	std::regex blank_line_regex = R"(^(?:[\t ]*(?:\r?\n|\r))+)";
	std::regex comment_line_regex = R"(^[\t ]*[/][*][^*]*[*]+([^/*][^*]*[*]+)*[/]|^[\t ]*([/][/]).*)";
};

}
