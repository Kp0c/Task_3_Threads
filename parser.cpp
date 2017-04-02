#include "parser.h"

namespace parser {

Statistic Parser::Parse(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios::in);
	Statistic stat {0,0,0,0};

	if (file.is_open())
	{
		std::string text;

		text.assign(std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>());

		stat.line_count = std::count(text.begin(),text.end(),'\n');

		auto begin = std::sregex_iterator(text.begin(), text.end(), blank_line_regex);
		auto end = std::sregex_iterator();

		stat.blank_lines = std::distance(begin, end);

		begin = std::sregex_iterator(text.begin(),text.end(), comment_line_regex);

		stat.comment_lines = 0;
		for(auto i = begin; i != end; ++i)
			{
				std::smatch match = *i;
				std::string str = match.str();
				stat.comment_lines += std::count(str.begin(), str.end(), '\n') + 1;
			}

		stat.code_lines = stat.line_count - (stat.blank_lines + stat.comment_lines);
		file.close();
	}

	return stat;
}

}
