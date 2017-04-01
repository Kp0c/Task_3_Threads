#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include <exception>
#include <queue>
#include <regex>

namespace scaner {

class Scaner{
	//Scan path for file with certain extension, and for each path to found files call callback function
	void Scan(std::string path, std::regex extension_pattern, std::function<void(std::string)> callback);
};

}
