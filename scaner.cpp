#include "scaner.h"

namespace scaner {

void Scaner::Scan(std::string path, std::regex extension_pattern, std::function<void (std::string)> callback)
{
	recursive_directory_iterator end_iter;

	if(!exists(path))
		throw std::invalid_argument(path + " doesn't exist!");

	for (recursive_directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr)
	{
		try
		{
			if ( is_regular_file( dir_itr->status() ) )
			{
				if (std::regex_match(dir_itr->path().extension().string(), extension_pattern))
				{
					callback(dir_itr->path().string());
				}
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
		}
	}
}

}

