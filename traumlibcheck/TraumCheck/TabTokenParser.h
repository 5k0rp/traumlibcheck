#pragma once

#include <string>

class TabTokenParser
{
public:
	TabTokenParser() {}

	const char* getToken(int& data, const char* line) const;
	const char* getToken(std::string& data, const char* line) const;
};