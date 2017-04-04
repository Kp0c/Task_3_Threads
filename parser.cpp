#include "parser.h"

namespace parser
{

void Parser::Parse(std::string path, Statistic* stat)
{
	std::ifstream file;
	file.open(path, std::ios::in);

	if(stat == nullptr)
	{
		throw std::invalid_argument("stat cannot be null");
	}

	if (file.is_open())
	{
		stat->processed_files++;

		bool is_in_multiline = false;
		std::string line;
		std::string first_two_symbols;

		int code_lines = 0;
		int comment_lines = 0;
		int blank_lines = 0;
		while (getline (file,line))
		{
			line.erase(std::remove_if(line.begin(), line.end(), [] (char c) {
				return c == ' ' || c == '\t';
			}));

			if(line.empty())
			{
				blank_lines++;
			}
			else if(is_in_multiline)
			{
				comment_lines++;
				if(line.find("*/") != std::string::npos)
				{
					//duct tape for "*/" situations (it's blank line)
					if(line.substr(0,2) == "*/")
					{
						blank_lines++;
						comment_lines--;
					}

					if(line.find("/*") == std::string::npos)
					{
						is_in_multiline = false;
					}
				}
			}
			else
			{
				first_two_symbols = line.substr(0,2);
				if(first_two_symbols == "//")
				{
					comment_lines++;
				}
				else if (first_two_symbols == "/*")
				{
					comment_lines++;
					is_in_multiline = true;
				}
				else
				{
					code_lines++;
					//duct tape for "<code>/*" situations (it's code line) ¯\_(ツ)_/¯
					if(line.find("/*") != std::string::npos)
					{
						is_in_multiline = true;
					}
				}
			}
		}

		//add gathered information
		stat->code_lines += code_lines;
		stat->comment_lines += comment_lines;
		stat->blank_lines += blank_lines;
		stat->line_count += code_lines + comment_lines + blank_lines;

		//close file
		file.close();
	}
}

}
