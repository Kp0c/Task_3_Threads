#include "parser.h"

namespace parser
{

void Parser::Parse(std::string path, std::shared_ptr<Statistic> stat)
{
	std::ifstream file;
	file.open(path, std::ios::in);

	if(stat == nullptr)
	{
		throw std::invalid_argument("Stat cannot be null");
	}

	if(file.is_open())
	{
		stat->processed_files++;

		int code_lines = 0;
		int comment_lines = 0;
		int blank_lines = 0;

		bool is_in_multiline = false;
		std::string line;
		while (getline(file,line))
		{
			std::locale locale;
			line.erase(std::remove_if(line.begin(), line.end(), [&locale] (char c)
			{
				return std::isspace(c, locale);
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
					//duct tape for "*/" situations (it's a blank line)
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
				std::string first_two_symbols = line.substr(0,2);
				if(first_two_symbols == "//")
				{
					comment_lines++;
				}
				else if(first_two_symbols == "/*")
				{
					comment_lines++;
					is_in_multiline = true;
				}
				else
				{
					code_lines++;
					//duct tape for "<code>/*" situations (it's a code line) ¯\_(ツ)_/¯
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
