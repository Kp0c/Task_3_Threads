#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <functional>
#include <regex>

namespace ProjectParser
{

class Scaner
{
public:
	static void Scan(std::string path, std::regex extension_pattern,
			std::function<void(std::string)> callback,
			std::function<void()> done_callback);
};

} // namespace ProjectParser
