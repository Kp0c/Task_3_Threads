#pragma once
#include <string>
#include <regex>

namespace parser {

struct Statistic
{
	int blank_lines;
	int comment_lines;
	int code_lines;
};

class Parser
{
public:
	Statistic Parse(std::string path);
private:
	std::regex blank_line_regex = R"(^(?:[\t ]*(?:\r?\n|\r))+)";
	std::regex comment_line_regex = R"(^[\t ]*[/][*][^*]*[*]+([^/*][^*]*[*]+)*[/]|^[\t ]*([/][/]).*)";
};


}
