#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include <exception>
#include <functional>
#include <queue>
#include <regex>

namespace scaner {

class Scaner{
public:
	void Scan(const std::string& path, std::regex extension_pattern, std::function<void(std::string)> callback);
};

}
