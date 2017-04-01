#include "parser.h"

namespace parser {

void Parser::Parse(std::string path)
{
	std::ifstream file;
	file.open(path, ios::in);
	Statistic stat;

	if (file.is_open())
	{
		std::string text (std::istreambuf_iterator<char>(file),
						  std::istreambuf_iterator<char>());

		stat.blank_lines = std::regex_search(text, blank_line_regex);
		/*std::string line;
		while ( getline (file,line) )
		{
			if(line == "")
			{
				stat.blank_lines++;
			}
			else
			{
				line = line.substr(line.find_first_not_of('\t'));
				std::string comment_line = line.substr(line.find_first_not_of(' '));
				//comment_line = comment_line.substr(comment_line.find_first_not_of('\t'),2);
				if(line.substr(0,2) == "//")
				{
					stat.comment_lines++;
				}
				else
					stat.code_lines++;
			}
		}*/
		file.close();
	}
}

}
