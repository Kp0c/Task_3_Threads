#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include <exception>
#include <queue>

#include "mutexFileQueue.h"
#include "file.h"

class Scaner
{
public:
	//Scan results will be in this container
	Scaner(MutexFileQueue* container) : m_container(container) { }

	//Scan folder at path and all subfolders for .c, .cpp, .h and .hpp files
	void Scan(std::string path, std::function<void(File)> callback)
	{
		boost::filesystem::directory_iterator end_iter;
		std::queue<boost::filesystem::directory_iterator> foldersToScan;

		if(!boost::filesystem::exists(path))
			throw std::invalid_argument(path + " doesn't exist!");
		boost::filesystem::directory_iterator dir_itr;
		foldersToScan.push(boost::filesystem::directory_iterator(path));

		while(!foldersToScan.empty())
		{
			dir_itr = foldersToScan.front();
			foldersToScan.pop();
			for (; dir_itr != end_iter; ++dir_itr )
			{
				try
				{
					if ( boost::filesystem::is_directory( dir_itr->status() ) )
					{
						//std::cout << dir_itr->path().filename() << " [directory]\n";
						foldersToScan.push(boost::filesystem::directory_iterator(dir_itr->path()));
					}
					else if ( boost::filesystem::is_regular_file( dir_itr->status() ) )
					{
						std::string extension = dir_itr->path().extension().string();
						if (extension == ".cpp" || extension == ".c" ||
							extension == ".hpp" || extension == ".h")
						{
							//m_container->add(File(dir_itr->path().string()));
							callback(File(dir_itr->path().string()));
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

private:
	MutexFileQueue* m_container;
	std::function<void(File)> callback;
};
