#include "common.h"

#include "TabTokenParser.h"

#include <stdlib.h>


const char* TabTokenParser::getToken(int& data, const char* line) const
{
	if(!*line)
		return line;

	char intbuf[32];
	
	int pos = 0;
	for(; *line && *line != '\t'; ++line)
		if(pos < 31)
			intbuf[pos++] = *line;
	intbuf[pos] = 0;

	data = static_cast<int>(atof(intbuf));
	
	if(*line == '\t')
		++line;

	return line;
}

const char* TabTokenParser::getToken(std::string& data, const char* line) const
{
	for(; *line && *line != '\t'; ++line)
		data.push_back(*line);
	
	if(*line == '\t')
		++line;

	return line;
}