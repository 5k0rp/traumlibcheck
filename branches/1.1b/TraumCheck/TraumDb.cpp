#include "common.h"

#include "TraumDb.h"
#include "TabTokenParser.h"
#include "UnicodeConverter.h"

#include <windows.h>
#include <fstream>
#include <functional>

struct TraumDbLineBookParser : public TabTokenParser
{
	int id;
	int author;
	std::string name;
	std::string lang;
	int series;
	int number;
	int year;
	std::string transl;
	std::string bookPath;
	std::string bookFileName;
	int size;
	int asize;
	std::string added;

	TraumDbLineBookParser(const char* line);
};

TraumDbLineBookParser::TraumDbLineBookParser(const char* line)
{
	line = getToken(id, line);
	line = getToken(author, line);
	line = getToken(name, line);
	line = getToken(lang, line);
	line = getToken(series, line);
	line = getToken(number, line);
	line = getToken(year, line);
	line = getToken(transl, line);
	line = getToken(bookPath, line);
	line = getToken(bookFileName, line);
	line = getToken(size, line);
	line = getToken(asize, line);
	line = getToken(added, line);
}

TraumDb::TraumDb()
{
}

bool TraumDb::add(const wchar_t *pathdb)
{
	const std::streamsize bufSize = 2048;
	char readBuf[bufSize];

	std::ifstream db(pathdb);

	while(db){
		db.getline(readBuf, bufSize);
		if(db.eof())
			break;
		
		TraumDbLineBookParser book(readBuf);
	
		std::wstring path;
		ansi_to_unicode_convert(path, book.bookPath.c_str(), (unsigned int)book.bookPath.size(), 1251);

		std::wstring file;
		ansi_to_unicode_convert(file, book.bookFileName.c_str(), (unsigned int)book.bookFileName.size(), 1251);

		std::replace_if(path.begin(), path.end(), std::bind2nd(std::equal_to<wchar_t>(), L'/'), L'\\');
		
		path += file;
		path += L".zip";

		LibNodeCalalog::add(path.c_str(), book.asize);
	}

	return true;
}