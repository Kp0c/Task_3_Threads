#include "parser.h"

Parser::Parser(/*MutexQueue* files,*/ /*int threads_count = 5*/) /*: m_threads_count(threads_count), m_files(files)*/
{
	//threads = new std::thread[threads_count];
}

void Parser::Parse(std::string path)
{
	std::thread new_thread(ParseFile, path);
	new_thread.join();
}

void ParseFile(std::string path)
{
	std::ifstream file;
	file.open(path, ios::in);
	int blank_lines, comment_line, code_lines;

	if (file.is_open())
	{
		std::string line;
		while ( getline (file,line) )
		{
			if(line == "")
			{
				blank_lines++;
			}
			else
			{
				std::string comment_line = line.substr(line.find_first_not_of(' '));
				comment_line = comment_line.substr(comment_line.find_first_not_of('\t'),2);
				if(comment_line == "//")
				{
					comment_lines++;
				}
				else
					code_lines++;
			}
		}
		file.close();
	}

	std::cout << "File: " << path << std::endl;
	std::cout << "Blank lines: " << blank_lines << std::endl;
	std::cout << "Comment lines: " << comment_line << std::endl;
	std::cout << "Code lines: " << code_lines << std::endl;
}
