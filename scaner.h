#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include <functional>
#include <regex>

namespace scaner {

class Scaner{
public:
	void Scan(const std::string& path, std::regex extension_pattern, std::function<void(std::string)> callback,
			  std::function<void()> done_callback);
};

}
