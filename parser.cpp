#include "parser.h"

namespace parser {

Statistic* Parser::ParseRegex(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios::in);
	Statistic* stat  = new Statistic {0, 0, 0, 0, 0};

	if (file.is_open())
	{
		std::string text;

		text.assign(std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>());

		stat->line_count = std::count(text.begin(),text.end(),'\n');

		auto begin = std::sregex_iterator(text.begin(), text.end(), blank_line_regex);
		auto end = std::sregex_iterator();

		stat->blank_lines = std::distance(begin, end);

		begin = std::sregex_iterator(text.begin(),text.end(), comment_line_regex);

		stat->comment_lines = 0;
		for(auto i = begin; i != end; ++i)
		{
			std::smatch match = *i;
			std::string str = match.str();
			stat->comment_lines += std::count(str.begin(), str.end(), '\n') + 1;
		}

		stat->code_lines = stat->line_count - (stat->blank_lines + stat->comment_lines);
		file.close();
	}

	return stat;
}

void Parser::Parse(std::string path, Statistic* stat)
{
	std::ifstream file;
	file.open(path, std::ios::in);

	if (file.is_open())
	{
		stat->processed_files++;

		bool in_multiline = false;
		std::string line;
		std::string lineSub;

		int code_lines = 0;
		int comment_lines = 0;
		int blank_lines = 0;
		while ( getline (file,line) )
		{
			line.erase(std::remove_if(line.begin(), line.end(), [] (char c) {
				return c == ' ' || c == '\t';
			}));

			if(line == "")
			{
				blank_lines++;
			}
			else if(in_multiline)
			{
				comment_lines++;
				if(line.find("*/") != std::string::npos)
				{
					if(line.substr(0,2) == "*/")
					{
						blank_lines++;
						comment_lines--;
					}

					if(line.find("/*") == std::string::npos)
					{
						in_multiline = false;
					}
				}
			}
			else
			{
				lineSub = line.substr(0,2);
				if(lineSub == "//")
				{
					comment_lines++;
				}
				else if (lineSub == "/*")
				{
					comment_lines++;
					in_multiline = true;
				}
				else
				{
					code_lines++;
					if(line.find("/*") != std::string::npos)
						in_multiline = true;
				}
			}
		}

		//add gathered information
		stat->code_lines += code_lines;
		stat->comment_lines += comment_lines;
		stat->blank_lines += blank_lines;
		stat->line_count += code_lines + comment_lines + blank_lines;

		file.close();
	}
}

}
